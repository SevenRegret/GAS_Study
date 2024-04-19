// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;


/**
 * 
 */
UCLASS()
class MNB_GAS_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	// ��̬�����޷�����world�е��κ�Object����Ϊ������ܲ����ڣ���˾�̬������Ҫһ��������
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

};
