// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
namespace UT
{
class SerializationData;
}

class FPXConnectCommandHandler
{
public:
	FPXConnectCommandHandler();
	void handleCommand(UT::SerializationData* pData);
protected:
};
