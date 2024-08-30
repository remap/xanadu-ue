#pragma once
#ifdef IS_UNREAL
//using namespace std;
#include "UE_stdafx.h"
#endif
#include "UT_SerializationExtraTypes.h"
namespace UT
{
class SerializationData
{
public:
	SerializationData();
	SerializationData(int startingSize);
	SerializationData(char* pRawDataAdoptee,int rawDataSize);
	SerializationData(const string& srcFilePath);
	SerializationData(const SerializationData& src);
	SerializationData(SerializationData&& src) noexcept;
	~SerializationData();
#ifdef IS_UNREAL
	SerializationData* makeCopy() const;
#else
	SerializationData* makeCopy();
#endif
	void swap(SerializationData& swappee);
	void setCtAccessed(int ctAccessed);
	int getCtAccessed();
	int getRawDataSize() const;
	void setRawData(const char* pRawData,int rawDataSize);
	void adoptRawData(char* pRawData,int rawDataSize);
	char* getRawData(int& ctAccessed) const;
	char* relinquishRawData(int& ctAccessed);
	void shrinkDataToCtAccessed();
	void write(const void* pRawData,int ct);
	void overwrite(const void* pRawData,int offset,int ct);
	int read(void* pRawData,int ct);
	void appendToLog(const string& app,int posHint=-1);
	bool toFile(const string& path);
protected:
	void outputLog();
	string m_log;
	int m_ctAccessed;
	int m_rawDataSize;
	int m_extensionSize;
	char* m_pRawData;
};


}
