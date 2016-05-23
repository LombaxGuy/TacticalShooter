#include "TacticalShooter.h"
#include "TopDownCameraPawn.h"

ATopDownCameraPawn::ATopDownCameraPawn(const class FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	// Disable the default WASD movement of the pawn
	bAddDefaultMovementBindings = false;

	// Setting up camera defaults
	cameraRadius = 1000.0f;
	cameraZAngle = 0.0f;
	cameraHeightAngle = 70.0f;
	cameraZoomSpeed = 32.0f;
	cameraRadiusMin = 750.0f;
	cameraRadiusMax = 2000.0f;
	cameraMovementSpeed = 2000.0f;
	cameraScrollBoundary = 25.0f;

	canCameraMove = true;

	cameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("TopDown Camera"));
	cameraComponent->AttachParent = this->GetRootComponent();
	cameraComponent->bUsePawnControlRotation = false;
	RepositionCamera();

	PrimaryActorTick.bCanEverTick = true;
}

void ATopDownCameraPawn::SetupPlayerInputComponent(class UInputComponent *inputComponent)
{
	check(inputComponent);

	// Zoom camera controls
	inputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATopDownCameraPawn::ZoomIn);
	inputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATopDownCameraPawn::ZoomOut);

	inputComponent->BindAxis("MoveForward", this, &ATopDownCameraPawn::MoveCameraForward);
	inputComponent->BindAxis("MoveRight", this, &ATopDownCameraPawn::MoveCameraRight);
}

void ATopDownCameraPawn::ZoomIn()
{
	cameraRadius = FMath::Clamp(cameraRadius - cameraZoomSpeed, cameraRadiusMin, cameraRadiusMax);
	RepositionCamera();
}

void ATopDownCameraPawn::ZoomOut()
{
	cameraRadius = FMath::Clamp(cameraRadius + cameraZoomSpeed, cameraRadiusMin, cameraRadiusMax);
	RepositionCamera();
}

FRotator ATopDownCameraPawn::GetCameraYaw()
{
	return FRotator(0.0f, cameraComponent->ComponentToWorld.Rotator().Yaw, 0.0f);
}

void ATopDownCameraPawn::MoveCameraForward(float direction)
{
	float value = direction * localDeltaSeconds * cameraMovementSpeed;

	FVector deltaMove = value * GetCameraYaw().Vector();
	FVector newLoc = this->GetActorLocation() + deltaMove;

	if (GetActorLocation().X > -4800 && direction == 1.0f ||
		GetActorLocation().X < 4700 && direction == -1.0f)
	{
		SetActorLocation(newLoc);
	}
}

void ATopDownCameraPawn::MoveCameraRight(float direction)
{
	float value = direction * localDeltaSeconds * cameraMovementSpeed;

	FVector deltaMove = value * (FRotator(0.0f, 90.0f, 0.0f) + GetCameraYaw()).Vector();
	FVector newLoc = this->GetActorLocation() + deltaMove;

	if (GetActorLocation().Y < 4500 && direction == -1.0f ||
		GetActorLocation().Y > -4500 && direction == 1.0f)
	{
		SetActorLocation(newLoc);
	}
}

void ATopDownCameraPawn::RepositionCamera()
{
	FVector newLocation(0.0f, 0.0f, 0.0f);
	FRotator newRotation(0.0f, 0.0f, 0.0f);

	float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(cameraZAngle));
	float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(cameraZAngle));

	float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(cameraHeightAngle));
	float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(cameraHeightAngle));

	newLocation.X = cosCameraZAngle * cosCameraHeightAngle * cameraRadius;

	newLocation.Y = sinCameraZAngle * cosCameraHeightAngle * cameraRadius;

	newLocation.Z = sinCameraHeightAngle * cameraRadius;

	newRotation = (FVector(0.0f, 0.0f, 0.0f) - newLocation).Rotation();

	cameraComponent->SetRelativeLocation(newLocation);
	cameraComponent->SetRelativeRotation(newRotation);
}

void ATopDownCameraPawn::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	localDeltaSeconds = deltaSeconds;

	FVector2D mousePosition;
	FVector2D viewportSize;

	UGameViewportClient* gameViewport = GEngine->GameViewport;

	check(gameViewport);
	gameViewport->GetViewportSize(viewportSize);

	if (gameViewport->IsFocused(gameViewport->Viewport) && gameViewport->GetMousePosition(mousePosition) && canCameraMove)
	{
		//UE_LOG(LogTemp, Log, TEXT("Mouse Position: ( %f, %f)"), mousePosition.X, mousePosition.Y);
		//UE_LOG(LogTemp, Log, TEXT("Right Relative Position: %f"), viewportSize.X - mousePosition.X);
		UE_LOG(LogTemp, Log, TEXT("Pawn Position: (%f, %f)"), GetActorLocation().X, GetActorLocation().Y);

		if (mousePosition.X < cameraScrollBoundary)
		{
			MoveCameraRight(-1.0f);
		}
		else if (mousePosition.X > viewportSize.X - cameraScrollBoundary)
		{
			MoveCameraRight(1.0f);
		}

		if (mousePosition.Y < cameraScrollBoundary)
		{
			MoveCameraForward(1.0f);
		}
		else if (mousePosition.Y > viewportSize.Y - cameraScrollBoundary)
		{
			MoveCameraForward(-1.0f);
		}
	}
}
