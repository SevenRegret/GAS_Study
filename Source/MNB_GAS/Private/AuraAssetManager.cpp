// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	// TODO: insert return statement here

	check(GEngine);


	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);

	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();


	// �����Զ���Gamplaytag�ṹ�ĳ�ʼ��
	FAuraGameplayTags::InitializeNativeGameplayTags();
}
