// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Common/UdpSocketReceiver.h"
#include "Containers/Queue.h"
#include "Dom/JsonObject.h" 
#include "UObject/NoExportTypes.h"
#include "Sockets.h"
#include "PXConnectHeartbeatListener.generated.h"

/**
 * 
 */
class UPXConnectNwManager;

class PIXERA_CONNECT_API IPXConnectHeartbeatListenerProxy
{
public:
	virtual ~IPXConnectHeartbeatListenerProxy(){};

	virtual void load(UPXConnectNwManager* pManager) = 0;
	virtual void load(UPXConnectNwManager* pManager,TSharedPtr<FInternetAddr> pAddress) = 0;
	virtual bool getIsConnected() const = 0;
	virtual void listen() = 0;
	virtual void stop() = 0;
	virtual void handleDataReceived(const FArrayReaderPtr& InData, const FIPv4Endpoint& InEndpoint) = 0;
#if WITH_EDITOR
	virtual void SetTickableInEditor(bool bInTickInEditor) = 0;
#endif
};

UCLASS()
class PIXERA_CONNECT_API UPXConnectHeartbeatListener : public UObject
{
	GENERATED_BODY()
	
public:

	void load(class UPXConnectNwManager* pManager);
	void load(class UPXConnectNwManager* pManager, TSharedPtr<FInternetAddr> pAddress);
	void listen();
	void stop();
	void BeginDestroy() override;
	void enqueJson(TSharedPtr<FJsonObject> pJsonObject);
	void workJsonQueue();
protected:

	UPROPERTY()
	class UPXConnectNwManager* m_pManager;

	TUniquePtr<IPXConnectHeartbeatListenerProxy> m_pHeartbeatListenerProxy;
	TQueue<TSharedPtr<FJsonObject>> m_jsonQueue;

	TSharedPtr<FInternetAddr> m_pAddress;

};
