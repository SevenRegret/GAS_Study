// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	// �ɸ���Actor
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// begin���Context
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	//�����ʾ
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// ��������ģʽϸ����Ϣ
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// ��ǿ�����������Ϊ��ɫ�Դ���InputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);


	// move������
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

// �Զ����ƶ���������, �ṹΪInputActionValue
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// ������
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// ��ת��
	const FRotator Rotation = GetControlRotation();
	// ��ȡyaw����ת
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// ������ǰ����
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// ����pawn����Ч
	if (APawn* ControllorPawn = GetPawn<APawn>())
	{
		// �����ǰ�����ҵ��ƶ�����valueֵ��
		ControllorPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllorPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// ���������
	if (!CursorHit.bBlockingHit) return;

	// ��һ֡
	LastActor = ThisActor;
	// ��ǰ֡, ��ȡ��Actor
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	// ����Actor�߼�
	// �����һָ֡��AcotrΪ��
	if (LastActor == nullptr)
	{
		// ��ǰ����
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
		else
		{
			// ��ǰҲ�գ�ɶ������
		}
	}
	else
	{
		// ��һ֡���գ���ǰ֡��
		if (ThisActor == nullptr)
		{
			// ��һָ֡���Ŀ��ȡ������
			LastActor->UnHighlightActor();
		}
		else
		{
			// ����Ŀ�굫����ͬ��ȡ����֡Ŀ�꣬���õ�ǰĿ�����
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}
