#pragma once
#include "UT_Serialization.h"
namespace UT
{
class SerializationHelper
{
public:
	SerializationHelper(bool isWrite,int startingSize=1024);
	SerializationHelper(char* pRawDataAdoptee,int rawDataSize);
	~SerializationHelper();
	void reserveCount();
	void incCount();
	void writeCount();
	SerializationData& getData();
	SerializationData* releaseData();
protected:
	SerializationData* pData;
public:
	SerializationConverter converter;
	SerializationContext context;
	int m_storedCtAccessed;
	int m_count;
	
};

}
