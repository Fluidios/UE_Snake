#include "Food.h"
#include "SnakeBase.h"

// Устанавливает значения по умолчанию
AFood::AFood()
{
	// Настройте этот объект actor на вызов Tick() для каждого кадра. Вы можете отключить эту функцию, чтобы повысить производительность, если она вам не нужна.
	PrimaryActorTick.bCanEverTick = true;
}

// Вызывается при запуске игры или при возрождении
void AFood::BeginPlay()
{
	Super::BeginPlay();
}

// Вызывается каждый кадр
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead) {
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake)) {
			Snake->AddElementsToSnakeTale(1);
			FVector newPosition = FMath::VRand();
			newPosition.X *= SpawnZone.X;
			newPosition.Y *= SpawnZone.Y;
			newPosition.Z = this->GetActorLocation().Z;
			this->SetActorLocation(newPosition);
		}
	}
}
