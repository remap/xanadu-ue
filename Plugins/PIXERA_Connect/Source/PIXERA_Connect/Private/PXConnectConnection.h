// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Common/UdpSocketReceiver.h"
#include "UObject/NoExportTypes.h"
#include "Misc/ScopeLock.h"
#include "Containers/Queue.h"
#include "Sockets.h"
#include "PXConnectBinaryHelp.h"
#include "PXConnectSerializationExtraTypes.h"
#include "PXConnectConnection.generated.h"

/**
 * 
 */

namespace AV
{
namespace UnrealSerializationHelper
{
struct UnrealSerStruct;
struct UnrealEntitySerializationStruct;
}
}

class UPXConnectNwManager;

class PIXERA_CONNECT_API IPXConnectConnectionProxy
{
public:
	virtual ~IPXConnectConnectionProxy(){};

	virtual bool load(UPXConnectNwManager* pManager) = 0;
	virtual void setAttributes(const FIPv4Address& adress,const unsigned int port,const FString& clientName) = 0;
	virtual bool getIsConnected() const = 0;
	virtual void initTcpConnection() = 0;
	virtual void initTcpConnection(const FIPv4Address& ip) = 0;
	virtual void sendData(char* pData,int dataSize) = 0;
	virtual void sendFromContext(TSharedPtr<FExecutionContext, ESPMode::ThreadSafe> pCtx) = 0;
	virtual void stop() = 0;
#if WITH_EDITOR
	virtual void SetTickableInEditor(bool bInTickInEditor) = 0;
#endif
};

struct SerStructInterpolation
{
	SerStructInterpolation(AV::UnrealSerializationHelper::UnrealEntitySerializationStruct* pInTargetStruct,
		AActor* pInActor,double inDuration);
	~SerStructInterpolation();
	bool operator==(const SerStructInterpolation& other);
	void reset();
	void apply();
	AActor* pActor;
	AV::UnrealSerializationHelper::UnrealEntitySerializationStruct* pTargetStruct;
	double timeWhenReceived;
	double duration;
	int ticks;
	int currentTick;
	bool isDone;
};

UCLASS()
class PIXERA_CONNECT_API UPXConnectConnection : public UObject
{
	GENERATED_BODY()

public:

	bool getIsConnected();
	bool load(class UPXConnectNwManager* pManager);
	void initTcpConnection();
	void initTcpConnection(const FIPv4Address& ip);
	void sendData(char* pData,int dataSize);
	void sendFromContext(TSharedPtr<FExecutionContext, ESPMode::ThreadSafe> pCtx);
	bool stop();
	bool getIsProxyConnected();
	void BeginDestroy() override;
	void enqueExecCtx(TSharedPtr<FExecutionContext, ESPMode::ThreadSafe> pExecutionContext);
	void workExecCtxQueue();
	void enqueRawSerData(char* pData,uint32 dataSize);
	void workSerDataQueue();
	AActor* getActorFromName(const FString& actorName);
protected:

	UPROPERTY()
	class UPXConnectNwManager* m_pManager;

	TUniquePtr<IPXConnectConnectionProxy> m_pConnectionProxy;
	TQueue<TSharedPtr<FExecutionContext, ESPMode::ThreadSafe>> m_executionContextQueue;
	
	TArray<UT::SerializationData*> m_serDataQueue;
	std::list<std::unique_ptr<SerStructInterpolation>> m_interpolationStructList;
	TAtomic<int> m_serDataQueueLastWriteIndex;
	TAtomic<int> m_serDataQueueLastReadIndex;
	TAtomic<int> m_serDataQueueSize;
};