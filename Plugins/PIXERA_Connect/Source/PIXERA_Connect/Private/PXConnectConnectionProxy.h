// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IPAddress.h" 
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Common/UdpSocketReceiver.h"
#include "Common/TcpListener.h"
#include "PXConnectNwPacket.h"

#include "Tickable.h"
#include "HAL/Runnable.h"
#include "PXConnectConnection.h"

/**
 * 
 */
class UPXConnectNwManager;

class PIXERA_CONNECT_API FPXConnectConnectionProxy : public IPXConnectConnectionProxy, public FTickableGameObject, public FRunnable
{
public:
	FPXConnectConnectionProxy(class UPXConnectConnection& inConnection);
	virtual ~FPXConnectConnectionProxy();

	bool load(UPXConnectNwManager* pManager) override;
	void setAttributes(const FIPv4Address& adress, const unsigned int port, const FString& clientName) override;
	bool getIsConnected() const override;
	void initTcpConnection() override;
	void initTcpConnection(const FIPv4Address& ip) override;
protected:
	void startListeningThread();
public:
	void sendData(char* pData, int dataSize) override;
	void sendFromContext(TSharedPtr<FExecutionContext, ESPMode::ThreadSafe> pCtx) override;
	void stop() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return getIsConnected(); }
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

#if WITH_EDITOR
	void SetTickableInEditor(bool inTickInEditor) override;
	virtual bool IsTickableInEditor() const override;
#endif
protected:
	void listenForData();
	void createExceutionContextAndPostToManager(char* pData,uint32 dataSize);
	void postPacketDataToManager(char* pData, uint32 dataSize);
	UPROPERTY()
	UPXConnectConnection* m_pConnection;
	FSocket* m_pTcpSocket;

	FIPv4Address m_address;
	int32 m_port;

	TUniquePtr<FRunnableThread> m_pThread;
	FCriticalSection m_criticalSection;
	bool m_isListening;

	TAtomic<bool> m_isConnected = false;

	std::unique_ptr<PXConnectNwPacket> m_pNwPacket;
	TMap<SequenceNumber, TSharedPtr<FExecutionContext, ESPMode::ThreadSafe>> m_executionContexts;

	FString m_socketName;
#if WITH_EDITOR
	bool m_tickInEditor;
#endif

};
