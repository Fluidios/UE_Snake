#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElementBase.generated.h"
class UStaticMeshComponent;
class ASnakeBase;

UCLASS()
class SNAKE_API ASnakeElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	// Устанавливает значения по умолчанию для свойств этого объекта actor
	ASnakeElementBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		UStaticMeshComponent* MeshComponent;
	UPROPERTY()
		FVector TargetPosition;
	UPROPERTY()
		bool TargetExist;
	UPROPERTY()
		ASnakeBase* OwnerSnake;
	UPROPERTY(BlueprintReadOnly)
		bool isAHeadElement;
protected:
	// Вызывается при запуске игры или при возрождении
	virtual void BeginPlay() override;

public:
	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;
	void SetTargetPosition(FVector newTargetPosition);
	UFUNCTION(BlueprintNativeEvent)
	void SetupAsSnakeHead();
	void SetupAsSnakeHead_Implementation();
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	UFUNCTION()
		void HandleBeginOverlap(
			UPrimitiveComponent* overlapedComponent,
			AActor* otherActor,
			UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex, 
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
		void ToggleCollision();
};
