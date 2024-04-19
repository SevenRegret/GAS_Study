// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// ί��
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);


	// GameplayTags��ȡ����
	//const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	////GameplayTags.Attributes_Secondary_Armor.ToString();
	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	10.f,
	//	FColor::Orange,
	//	FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
	//);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		// Spec���õ�Ab��Ϣ
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			// ����AB
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	// �������Ѿ������AB�б���
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// �ϸ�ƥ��InputTag
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// �������֪ͨAb������������һ��pressed״̬
			AbilitySpecInputPressed(AbilitySpec);

			if (!AbilitySpec.IsActive())
			{
				// ���Լ���AB
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	// �������Ѿ������AB�б���
	/*for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			// �ϸ�ƥ��InputTag
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				// �������֪ͨAb������������һ��pressed״̬
				AbilitySpecInputPressed(AbilitySpec);

				if (!AbilitySpec.IsActive())
				{
					// ���Լ���AB
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
		*/

}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	// �������Ѿ������AB�б���
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// �ϸ�ƥ��InputTag
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// �������֪ͨAb������������һ��pressed״̬
			AbilitySpecInputReleased(AbilitySpec);
		}
	}

}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(
	UAbilitySystemComponent* AbilitySystemComponent, 
	const FGameplayEffectSpec& EffectSpec, 
	FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied"));

	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
