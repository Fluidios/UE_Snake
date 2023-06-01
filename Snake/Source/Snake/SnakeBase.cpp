#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Устанавливает значения по умолчанию
ASnakeBase::ASnakeBase()
{
	// Настройте этот объект actor на вызов Tick() для каждого кадра. Вы можете отключить эту функцию, чтобы повысить производительность, если она вам не нужна.
	PrimaryActorTick.bCanEverTick = true;
	StartSnakeLength = 3;
	SnakeElementsSize = 100.f;
	SnakeMoveSpeed = 0.1f;
	MovementDirection = EDirection::Up;
}

// Вызывается при запуске игры или при возрождении
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(SnakeMoveSpeed);
	AddElementsToSnakeTale(StartSnakeLength);
}

// Вызывается каждый кадр
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* overlapedElement, AActor* other)
{
	if (IsValid(overlapedElement)) {
		IInteractable* interactableElement = Cast<IInteractable>(other);
		if (interactableElement) {
			interactableElement->Interact(this, overlapedElement->isAHeadElement);
		}
	}
}

void ASnakeBase::GameOver()
{
	UE_LOG(LogTemp, Display, TEXT("Game over!"));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->RestartLevel();
	//this->Destroy();
}

void ASnakeBase::AddElementsToSnakeTale(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		FVector position;
		FTransform transform;
		if (SnakeElements.Num() == 0)
		{
			position = GetActorLocation();
			transform = FTransform(position);
		}
		else
		{
			auto lastElement = SnakeElements[SnakeElements.Num() - 1];
			position = lastElement->GetActorLocation();
			transform = FTransform(position);
		}
		ASnakeElementBase* newSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, transform);
		newSnakeElement->OwnerSnake = this;
		newSnakeElement->SetTargetPosition(position);
		if (SnakeElements.Add(newSnakeElement) == 0) 
		{
			newSnakeElement->SetupAsSnakeHead();
		}
	}
}

void ASnakeBase::Move()
{
	FVector MoveVector;
	float speed = SnakeElementsSize;
	switch (MovementDirection)
	{
	case EDirection::Up:
		MoveVector.X = speed;
		break;
	case EDirection::Down:
		MoveVector.X = -speed;
		break;
	case EDirection::Left:
		MoveVector.Y = -speed;
		break;
	case EDirection::Right:
		MoveVector.Y = speed;
		break;
	}
	if (TurnWasExecuted) {
		SnakeElements[0]->ToggleCollision();
		TurnWasExecuted = false;
	}
	if (LastExecutedMoveDirection != MovementDirection)
	{
		SnakeElements[0]->ToggleCollision();
		TurnWasExecuted = true;
	}

	AddActorWorldOffset(MoveVector);

	for (size_t i = SnakeElements.Num()-1; i > 0; i--)
	{
		SnakeElements[i]->SetTargetPosition(SnakeElements[i - 1]->GetActorLocation());
	}
	SnakeElements[0] ->SetTargetPosition(GetActorLocation());
	LastExecutedMoveDirection = MovementDirection;
}
