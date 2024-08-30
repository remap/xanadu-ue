#pragma once
#include "UT_SerializationExtraTypes.h"
#ifndef IS_UNREAL
#include "UT_InterthreadId.h"
#else
#include <set>
using namespace std;
#endif
namespace UT
{
class SerializationData;
#ifndef IS_UNREAL
class InterthreadIdBank;
typedef map<InterthreadId,InterthreadId> ReIdMap;
typedef std::set<InterthreadId> ReIdSet;
#endif
class SerializationConverter
{
public:
	SerializationConverter(SerializationData& data,bool isWrite,bool withAtomKinds=true);
	~SerializationConverter();
	void reset(bool isWrite);
	SerializationData& getData();
	bool getIsWrite();
	void setCtCurrentChunkEnd(int ctCurrentChunkEnd);
	int getCtCurrentChunkEnd();
#ifndef IS_UNREAL
	void setDoReId(bool doReId,InterthreadIdBank* pIdBank);
	bool getDoReId();
	void addSparedFromReId(const InterthreadId& sparedId);
	void addSparedFromReId(const ReIdSet& spared);
	ReIdSet getSparedFromReId();
#endif
	SerAtomKinds peekAtNextAtomKind(SerAtomKinds eExpectedAtomKind);
#ifndef IS_UNREAL
	void next(InterthreadId& id);
#endif
	void next(bool& val);
	void next(char& val);
	void next(unsigned char& val);
	void next(short& val);
	void next(unsigned short& val);
	void next(int& val);
	void next(unsigned int& val);
	void next(int64& val);
	void next(uint64& val);
	void next(float& val);
	void next(double& val);
#ifndef IS_UNREAL
	void next(miVec2& val);
	void next(miVec3& val);
	void next(mhVec2& val);
	void next(mhVec3& val);
	void next(mlVec3& val);
	void next(mhVec4& val);
	void next(mhMat3& val);
	void next(mhMat4& val);
	void next(mhQuat& val);
#endif
	void next(string& str);
	void next(const string& str);
	void next(unique_ptr<string>* ppStrPtr);
	void next(char** ppBuffer,int& ct);
	void next(char* pBuffer,int ct);
	void next(vector<char>& buffer);
#ifndef IS_UNREAL
	template<typename T>
	void next(Array<T>& array)
	{
		int ct = array.size();
		this->next(ct);
		if(ct == 0)
		{
			array.clearQuick();
			return;
		}
		if(!m_isWrite)
		{
			array.resize(ct);
		}
		for(int i = 0; i < ct; ++i)
		{
			this->next(array.getReference(i));
		}
	}
	template<typename T>
	void next(juce::Rectangle<T>& val)
	{
		T x = val.getX();
		T y = val.getY();
		T w = val.getWidth();
		T h = val.getHeight();
		this->next(x);
		this->next(y);
		this->next(w);
		this->next(h);
		if(!m_isWrite)
		{
			val.setBounds(x, y, w, h);
		}
	}
#endif
	template<typename T>
	void nextSmallEnums(set<T>& set)
	{
		int ct = (int)set.size();
		this->next(ct);
		if(ct == 0)
		{
			set.clear();
			return;
		}
		if(m_isWrite)
		{
			for(T entry : set)
			{
				this->nextSmallEnum(&entry);
			}
		}
		else
		{
			T entry;
			for(int iii = 0; iii < ct; ++iii)
			{
				this->nextSmallEnum(&entry);
				set.insert(entry);
			}
		}
		
	}
	void nextSmallEnum(void* pVal);
	void next(SerializationData** ppSerData);
	void overwriteInt(int offsetPre,int val);
	bool moveToOptionalChunk(SerOptChunkId goalOptId,bool skipOtherOptionalChunks=true);
protected:
	void readWrite(SerAtomKinds eKind,void* pData,int ct);
public:
	void checkAtomKinds(SerAtomKinds eGoalKind,SerAtomKinds eReadKind);
protected:
	bool moveBeyondOptionalChunks();
	bool m_isWrite;
	bool m_withAtomKinds;
	int m_ctCurrentChunkEnd;
#ifndef IS_UNREAL
	InterthreadIdBank* m_pReIdBank;
	unique_ptr<ReIdMap> m_pReIdMap;
#endif
	SerializationData& m_data;
#ifdef DEBUG
public:
	SerOptChunkId m_nextOptionalChunkId;
#endif // DEBUG

};

}
