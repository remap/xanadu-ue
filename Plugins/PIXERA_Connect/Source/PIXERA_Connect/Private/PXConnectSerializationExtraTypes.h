#pragma once
#include "CoreMinimal.h"
#include "UT/UT_SerializationData.h"
#include "PXconnectSerializationExtraTypes.generated.h"

USTRUCT()
struct FSerDataHolder
{
	GENERATED_BODY()
	FSerDataHolder()
	{

	}

	FSerDataHolder(char* pData, uint32 dataSize)
	{
		serData.adoptRawData(pData, dataSize);
	}

	void adoptSerData(char* pData, uint32 dataSize)
	{
		serData.adoptRawData(pData, dataSize);
	}

	FSerDataHolder operator=(const FSerDataHolder& inCtx)
	{
		FSerDataHolder tmpCtx;

		int rawDataSize = inCtx.serData.getRawDataSize();
		if(rawDataSize > 0)
		{
			int ctAccessed = 0;
			auto pRawData = inCtx.serData.getRawData(ctAccessed);

			char* pRawDataCopy = new char[rawDataSize];
			::memcpy(pRawDataCopy, pRawData, rawDataSize);

			tmpCtx.serData.adoptRawData(pRawDataCopy, rawDataSize);
		}

		return tmpCtx;
	}

	UT::SerializationData serData;
};