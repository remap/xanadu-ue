// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/object.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Common/UdpSocketReceiver.h"

#include "Tickable.h"
#include "PXConnectHeartbeatListener.h"
/**
 * 
 */

class UPXConnectNwManager;

class PIXERA_CONNECT_API FPXConnectHeartbeatListenerProxy : public IPXConnectHeartbeatListenerProxy, public FTickableGameObject
{
public:
	FPXConnectHeartbeatListenerProxy(class UPXConnectHeartbeatListener& inListener);
	virtual ~FPXConnectHeartbeatListenerProxy();

	void load(UPXConnectNwManager* pManager) override;
	void load(UPXConnectNwManager* pManager, TSharedPtr<FInternetAddr> pAddress) override;
	bool getIsConnected() const override;
	void listen() override;
	void stop() override;
	void handleDataReceived(const FArrayReaderPtr& InData, const FIPv4Endpoint& InEndpoint) override;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return getIsConnected(); }
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;

#if WITH_EDITOR
	void SetTickableInEditor(bool bInTickInEditor) override;
	virtual bool IsTickableInEditor() const override;
#endif

	UPROPERTY()
	UPXConnectHeartbeatListener* m_pHeartbeatListener;

	FSocket* m_pSocket;
	FUdpSocketReceiver* m_pSocketReceiver;
	FString m_listenerName;
	bool m_isConnected;
	TSharedPtr<FInternetAddr> m_pAddress;
#if WITH_EDITOR
	bool m_tickInEditor;
#endif
};
