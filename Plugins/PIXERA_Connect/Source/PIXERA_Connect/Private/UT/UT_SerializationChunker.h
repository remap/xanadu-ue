#pragma once
#include "UT_SerializationExtraTypes.h"
#ifdef IS_UNREAL
using namespace std;
#endif
namespace UT
{
class SerializationContext;
class SerializationData;
class SerializationChunker
{
public:
	SerializationChunker(SerializationContext& context,SerChunkVersion version,const string& tag,SerOptChunkId optId=serOptChunkIdNone);
	SerializationChunker(SerializationContext& context,const string& tag,SerOptChunkId optId=serOptChunkIdNone);
	~SerializationChunker();
	bool checkVersion(SerChunkVersion version=1,bool doSkipData=true);
	static bool peekAtChunkHeader(SerializationContext& context,string& tag,int& size,bool resetCtAccessed=true,bool logFailure=true);
	static bool peekAtChunkHeader(SerializationData& data,string& tag,int& size,bool resetCtAccessed=true,bool logFailure=true);
	static bool peekAtChunkOptionality(SerializationData& data,SerOptChunkId& optId,int& size);
protected:
	void begin(SerializationContext& context,SerChunkVersion version,const string& tag,SerOptChunkId optId);
	void end();
	bool moveToNextNonOptionalChunk();
	SerializationContext& m_context;
	SerializationData& m_data;
	bool m_isWrite;
	SerChunkVersion m_readVersion;
	int m_size;
	int m_ctAccessedPre;
	int m_ctChunkEndPre;
};
}
