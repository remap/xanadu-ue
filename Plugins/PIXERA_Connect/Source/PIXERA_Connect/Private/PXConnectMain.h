// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PXConnectNwManager.h"
#include "PXConnectRootObjects.h"
#include "PXConnectMain.generated.h"

/**
 * 
 */
UCLASS()
class PIXERA_CONNECT_API UPXConnectMain : public UObject
{
	GENERATED_BODY()
	
public:
	void pluginStarting(UWorld* pWorld);
	void pluginShuttingDown();
	void worldBeginPlay();
	UPXConnectRootObjects* getRootObjects();
	void worldDestroyed();
	UPXConnectNwManager* getNwManager();
	UWorld* getWorld();
	static UPXConnectMain* getInstance(bool doCreate=true,UWorld* pWorld=nullptr);
protected:
	static UPXConnectMain* s_pInst;
	static bool s_stopping;
	UWorld* m_pCachedWorld;
	TArray<FString> m_mapNames;
	UPROPERTY()
	class UPXConnectNwManager* m_pNwManager;

	UPROPERTY()
	class UPXConnectRootObjects* m_pRootObjects;
};
