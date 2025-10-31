#pragma once
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABlasterCharacter();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	void Move(const FInputActionValue& Value);
	
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	
};
