#include "BlasterCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

ABlasterCharacter::ABlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ABlasterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABlasterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlasterCharacter::Move);
		}
	}
}

void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ABlasterCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("MoveVector: %s"), *MoveVector.ToString());
	if (Controller != nullptr)
	{
		// 获取摄像机朝向
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator YawRot(0, ControlRot.Yaw, 0);

		// 计算前向 / 右向向量
		const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		// 添加移动输入
		AddMovementInput(ForwardDir, MoveVector.X);
		AddMovementInput(RightDir, MoveVector.Y);
	}
}
