#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Wall.generated.h"

UCLASS()
class SNAKE_API AWall : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	// Устанавливает значения по умолчанию для свойств этого объекта actor
	AWall();

protected:
	// Вызывается при запуске игры или при возрождении
	virtual void BeginPlay() override;

public:
	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
