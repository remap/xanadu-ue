// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPv4/IPv4Address.h"
class UPXConnectMain;
class AActor;

unsigned long long PX_WORLD_DIFF_VOID = 0;

UWorld* getWorld();
FIPv4Address getUsedIp();
unsigned long long getParentWorldInterthreadDiff(AActor* pActor);
float getWorldToMeters();