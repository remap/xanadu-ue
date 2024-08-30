// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Common/UdpSocketReceiver.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Containers/Queue.h"
#include "PXConnectMain.h"
#include "UObject/Class.h"
#include "Engine/World.h"
#include "TimerManager.h"

class FPIXERA_ConnectModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void onWorldCreated(UWorld* pWorld,const UWorld::InitializationValues initValues);
	void onWorldBeginPlay();
	void onWorldDestroyed(UWorld* pWorld);
private:
	UWorld::FOnWorldBeginPlay::FDelegate m_beginPlayDelegate;
	bool m_mainLoaded;
};
