#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
UENUM()
enum class EDirection {
	Up,
	Down,
	Left,
	Right
};

UCLASS()
class SNAKE_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Устанавливает значения по умолчанию для свойств этого объекта actor
	ASnakeBase();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;
	UPROPERTY(EditDefaultsOnly)
	float SnakeElementsSize;
	UPROPERTY(EditDefaultsOnly)
	int StartSnakeLength;
	UPROPERTY(EditDefaultsOnly)
		float SnakeMoveSpeed;
	UPROPERTY()
	TArray <ASnakeElementBase*> SnakeElements;

	UPROPERTY()
		EDirection MovementDirection;
	UPROPERTY()
		EDirection LastExecutedMoveDirection;
	UPROPERTY()
		bool TurnWasExecuted;
protected:
	// Вызывается при запуске игры или при возрождении
	virtual void BeginPlay() override;
	void Move();

public:
	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void SnakeElementOverlap(ASnakeElementBase* overlapedElement, AActor* other);
	void AddElementsToSnakeTale(int amount = 1);
	void GameOver();
};
