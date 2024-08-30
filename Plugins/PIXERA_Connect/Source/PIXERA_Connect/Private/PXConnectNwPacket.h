// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PXConnectNwPacket
{
public:
	PXConnectNwPacket(uint32 headerSize);
	~PXConnectNwPacket();
	uint32 consumeData(char* pBufferData, uint32 ctBuffer,bool& isComplete);
	char* getData();
	char* getData(uint32& packetDataSize);
	void reset();
protected:
	uint32 m_dataSize;
	uint32 m_headerSize;
	uint32 m_availableSize;
	uint32 m_ctReadHeader;
	uint32 m_ctReadData;

	char* m_pHeader;
	char* m_pData;
};
