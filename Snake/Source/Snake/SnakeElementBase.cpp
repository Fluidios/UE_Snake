#include "SnakeElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Устанавливает значения по умолчанию
ASnakeElementBase::ASnakeElementBase()
{
	// Настройте этот объект actor на вызов Tick() для каждого кадра. Вы можете отключить эту функцию, чтобы повысить производительность, если она вам не нужна.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Вызывается при запуске игры или при возрождении
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Вызывается каждый кадр
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TargetExist)
	this->SetActorLocation(FMath::Lerp(this->GetActorLocation(), TargetPosition, 3*DeltaTime));
}

void ASnakeElementBase::SetTargetPosition(FVector newTargetPosition)
{
	TargetPosition = newTargetPosition;
	if (!TargetExist) {
		TargetExist = true;
	}
}

void ASnakeElementBase::SetupAsSnakeHead_Implementation()
{

	isAHeadElement = true;
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake)&&IsValid(OwnerSnake)) {
		if(OwnerSnake->SnakeElements.Num() > 3)
			OwnerSnake->GameOver();
	}
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* overlapedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OwnerSnake)) {
		OwnerSnake->SnakeElementOverlap(this, otherActor);
	}
}

void ASnakeElementBase::ToggleCollision()
{
	if(MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
