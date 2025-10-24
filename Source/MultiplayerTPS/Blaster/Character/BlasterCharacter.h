#pragma once
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABlasterCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
};
