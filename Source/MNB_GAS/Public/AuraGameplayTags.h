// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


/**
 *	�����Զ����ǩ, ����native Gameplay Tags�ĵ���
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get(){ return GameplayTags; }

	// ��ʼ��Tags
	static void InitializeNativeGameplayTags();

	// һ������
	FGameplayTag Attributes_Primary_Strength;

	FGameplayTag Attributes_Primary_Intelligence;

	FGameplayTag Attributes_Primary_Resilience;

	FGameplayTag Attributes_Primary_Vigor;



	// ��������Tag -- ����
	FGameplayTag Attributes_Secondary_Armor;

	FGameplayTag Attributes_Secondary_ArmorPenetration;

	FGameplayTag Attributes_Secondary_BlockChance;

	FGameplayTag Attributes_Secondary_CriticalHitChance;

	FGameplayTag Attributes_Secondary_CriticalHitDamage;

	FGameplayTag Attributes_Secondary_CriticalHitResistance;

	FGameplayTag Attributes_Secondary_HealthRegeneration;

	FGameplayTag Attributes_Secondary_ManaRegeneration;

	FGameplayTag Attributes_Secondary_MaxHealth;

	FGameplayTag Attributes_Secondary_MaxMana;

protected:


private:
	static FAuraGameplayTags GameplayTags;
};

