// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PXConnectNetworkExtraTypes.h"
#include "UT/UT_SerializationData.h"
#include "PXConnectBinaryHelp.generated.h"

#define LOCTEXT_NAMESPACE "PXConnectBinaryHelp"

unsigned int getPacketHeaderSize();
unsigned int analyzePacketHeader(const char* pHeader, unsigned int headerSize);
bool fillPacketHeader(char* pHeader,unsigned int headerSize,unsigned int dataSize);
typedef unsigned int SequenceNumber;
constexpr SequenceNumber g_sequenceNumberDefault = 0x80000000;

USTRUCT()
struct FExecutionContext
{
	GENERATED_BODY()

	FExecutionContext();
	FExecutionContext(char* pInData, uint32 inDataSize);

	void resetCtAccessed()
	{
		inData.setCtAccessed(0);
		outData.setCtAccessed(0);
	}
	FExecutionContext operator=(const FExecutionContext& inCtx)
	{
		FExecutionContext tmpCtx;

		/*int ctAccessed = 0;
		auto pInData = inCtx.inData.makeCopy();
		if(pInData)
		{
			tmpCtx.inData.adoptRawData(pInData->getRawData(ctAccessed), pInData->getRawDataSize());
		}
		auto pOutData = inCtx.outData.makeCopy();
		if(pOutData)
		{
			tmpCtx.outData.adoptRawData(pOutData->getRawData(ctAccessed), pOutData->getRawDataSize());
		}

		tmpCtx.seqNum = inCtx.seqNum;

		tmpCtx.onResponseDelegate = inCtx.onResponseDelegate;
		tmpCtx.responseNeedsExecutionInGameThread = inCtx.responseNeedsExecutionInGameThread;*/

		return tmpCtx;
	}

	void adoptCtxNetworkData(FExecutionContext& inCtx)
	{
		auto ctAccessed = 0;
		auto rawDataSize = inCtx.inData.getRawDataSize();
		auto pInData = inCtx.inData.relinquishRawData(ctAccessed);
		if(!pInData)
		{
			return;
		}
		
		inData.adoptRawData(pInData, rawDataSize);
		inData.setCtAccessed(ctAccessed);
	}

	bool operator<(const FExecutionContext& inCtx)
	{
		return seqNum < inCtx.seqNum;
	}

	bool operator>(const FExecutionContext& inCtx)
	{
		return seqNum > inCtx.seqNum;
	}

	DECLARE_DELEGATE_OneParam(FExecutionContextDelegate,FExecutionContext&);
	FExecutionContextDelegate onResponseDelegate;
	SequenceNumber seqNum;
	UT::SerializationData inData;
	UT::SerializationData outData;
	bool responseNeedsExecutionInGameThread;
};

USTRUCT()
struct FDispatchContext
{
	GENERATED_BODY()

	FDispatchContext()
		:delegateNeedsExecutionInGameThread(true)
	{}

	FDispatchContext(FExecutionContext::FExecutionContextDelegate inDelegate,bool executionInGameThread=true)
	{
		delegateNeedsExecutionInGameThread = executionInGameThread;
	}

	FDispatchContext operator=(const FDispatchContext& inCtx)
	{
		FDispatchContext tmpCtx(inCtx.dispatchDelegate,inCtx.delegateNeedsExecutionInGameThread);
		return tmpCtx;
	}

	FExecutionContext::FExecutionContextDelegate dispatchDelegate;
	bool delegateNeedsExecutionInGameThread;
};

SequenceNumber getNextSequenceNumber();
void prepDynamicPacket(FExecutionContext& ctx,SequenceNumber sequenceNumber, StackId& stackId);
void prepDynamicPacket(FExecutionContext& ctx);
void analyzeDynamicPacket(FExecutionContext& ctx,SequenceNumber& sequenceNumber, StackId& stackId);
void analyzeDynamicPacket(FExecutionContext& ctx);

void setVal_int(FExecutionContext& ctx,int val);
int getVal_int(FExecutionContext& ctx);
void setVal_uint(FExecutionContext& ctx,unsigned int val);
unsigned int getVal_uint(FExecutionContext& ctx);
void setVal_uchar(FExecutionContext& ctx,unsigned char val);
unsigned char getVal_uchar(FExecutionContext& ctx);
void setVal_double(FExecutionContext& ctx,double val);
double getVal_double(FExecutionContext& ctx);
void setVal_float(FExecutionContext& ctx,float val);
float getVal_float(FExecutionContext& ctx);
void setVal_bool(FExecutionContext& ctx,bool val);
bool getVal_bool(FExecutionContext& ctx);
void setVal_string(FExecutionContext& ctx,const std::string& str);
std::string getVal_string(FExecutionContext& ctx);

void addDispatch(const FString& funcName,FDispatchContext dispatchCtx);

typedef TMap<FString, FDispatchContext> FDispatchMap;

#undef LOCTEXT_NAMESPACE