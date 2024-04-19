// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;

class USplineComponent;

/**
 * 
 */
UCLASS()
class MNB_GAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Controller�д���һ��ָ��ָ��IMC
	UPROPERTY(EditAnywhere, Category = "Input");
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input");
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	// ������
	void CursorTrace();


	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	FHitResult CursorHit;

	// ABInput��������
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UAuraInputConfig> InputConfig;

	// ���һ��ASCָ��
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraASC();


	/// <summary>
	/// ʵ���������ɫ�ƶ���Ŀ��ص�
	/// 
	/// </summary>

	// Ŀ�귽��
	FVector CachedDestination = FVector::ZeroVector;
	// ���������¼�
	float  FollowTime = 0.f;
	// �̰������ж�����
	float ShortPressThreshold = 0.5f;
	// �Զ�����(�Զ����ٵ��ж���
	bool bAutoRunning = false;
	// �Ƿ�������׼ĳ��Ŀ�ꣿ
	bool bTargeting = false;
	// �Զ����ܵİ뾶��Χ
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	// �Զ����ܵ�������ʽ
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USplineComponent> Spline;

	// �Զ�����
	void AutoRun();
};
