#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "TopDownCameraPawn.generated.h"

/**
 *
 */
UCLASS()
class TACTICALSHOOTER_API ATopDownCameraPawn : public ASpectatorPawn
{
	GENERATED_BODY()

private:
	void SetupPlayerInputComponent(class UInputComponent *inputComponent);
	float localDeltaSeconds;

public:
	ATopDownCameraPawn(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent *cameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraZAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraHeightAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraZoomSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraRadiusMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraRadiusMin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float cameraScrollBoundary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		bool canCameraMove;

	UFUNCTION()
		void ZoomIn();

	UFUNCTION()
		void ZoomOut();

	UFUNCTION()
		FRotator GetCameraYaw();

	UFUNCTION()
		void MoveCameraForward(float direction);

	UFUNCTION()
		void MoveCameraRight(float direction);

	UFUNCTION()
		void RepositionCamera();

	UFUNCTION()
		virtual void Tick(float deltaSeconds) override;
};
