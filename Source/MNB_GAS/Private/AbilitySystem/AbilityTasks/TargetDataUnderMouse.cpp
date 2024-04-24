// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;

}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyConrolled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyConrolled)
	{
		SendMouseCursorData();
	}
	else
	{
		// �ȹ���һ��handle��һ��predictionkey
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		// ASCϵͳ�󶨸ú����ص�����Ҫ�Ĳ���ΪABSpechandle��ActivatePredictKey
		AbilitySystemComponent.Get()->
			AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).
			AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		// ����֮��ȷ������ί��
		const bool bCalledDelegate = 
			AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);

		// ��û���óɹ�
		if (!bCalledDelegate)
		{
			// ֪ͨ��������û����ί�У��ȴ�Զ�̵�������ݹ���
			SetWaitingOnRemotePlayerData();
		}
	}



}

// ���͹������
void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow SCopedPrediction(AbilitySystemComponent.Get());


	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;

	// ����Ŀ���Data
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	// data��Ӹ�Datahandle
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
	);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	// ���յ�Ŀ������ʱ�����õĺ�����

	// ���߿ͻ����Ѿ�����
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
