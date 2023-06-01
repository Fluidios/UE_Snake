#include "Wall.h"
#include "SnakeBase.h"

// Устанавливает значения по умолчанию
AWall::AWall()
{
	// Настройте этот объект actor на вызов Tick() для каждого кадра. Вы можете отключить эту функцию, чтобы повысить производительность, если она вам не нужна.
	PrimaryActorTick.bCanEverTick = true;
}

// Вызывается при запуске игры или при возрождении
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Вызывается каждый кадр
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AWall::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead) 
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake)) {
			Snake->GameOver();
		}
	}
}