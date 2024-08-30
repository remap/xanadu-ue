// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "PXConnectConnection.h"
#include "PXConnectHeartbeatListener.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonObject.h"
#include "PXConnectNwManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FNetworkInfos
{
	GENERATED_BODY()
public:
	FNetworkInfos(const FIPv4Address& inAddress,unsigned int inPort,const FString& inName)
	{
		address = inAddress;
		port = inPort;
		name = inName;
	}

	FNetworkInfos()
	{
			address = FIPv4Address();
			port = 0;
	}
	FIPv4Address address;
	unsigned int port;
	FString name;
};

UCLASS()
class PIXERA_CONNECT_API UPXConnectNwManager : public UObject
{
	GENERATED_BODY()

public:
	void listenToHeartBeat();
	void startConnection();
	void startConnection(const FIPv4Address& ip);
	void stopConnection();
	void stopHeartbeatListener();
	void setNetworkInfosReceiver(const FNetworkInfos& networkInfos);
	const FNetworkInfos& getNetworkInfosReceiver();
	void setNetworkInfosSender(const FNetworkInfos& networkInfos);
	const FNetworkInfos& getNetworkInfosSender();
	void BeginDestroy() override;
	void prepareDestruction();
	void analyzeReceivedJsonData(TSharedPtr<FJsonObject> pJsonObject,const FIPv4Address& adapterAddress);
	void sendData(char* pData,int dataSize);
	void setInterpolationTime(unsigned int interpolationTime);
	unsigned int getInterpolationTime();
	const FIPv4Address& getUsedIp();
protected:
	bool getIsAllowedToConnect(TSharedPtr<FJsonObject> pJsonObject);
	AActor* getActorFromObjectName(const FString& objectName);

	UPROPERTY(Transient)
	class UPXConnectConnection* m_pConnection;

	UPROPERTY(Transient)
	TArray<class UPXConnectHeartbeatListener*> m_heartBeatListeners;

	TMap<FString, AActor*> m_actors;

	FNetworkInfos m_networkInfosReceiver;
	FNetworkInfos m_netWorkInfosSender;

	FIPv4Address m_usedIp;

	int64 m_lastHeartbeatTime;
	int64 m_timeoutThreshold;

	TArray<TSharedPtr<FInternetAddr>> m_addresses;

	FString m_projectPath;
	FString m_exePath;
	FString m_pathToExecutable;
	FString m_clusterNodeId;
	unsigned int m_interpolationTime = 5;
};
