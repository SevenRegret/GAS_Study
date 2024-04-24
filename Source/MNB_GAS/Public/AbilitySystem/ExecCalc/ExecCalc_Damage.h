// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 *    �˺�����ִ��
 */
UCLASS()
class MNB_GAS_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:
    UExecCalc_Damage();

    // ִ�м����ຯ��ʱ����
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OoutExecutionOutput) const override;
};