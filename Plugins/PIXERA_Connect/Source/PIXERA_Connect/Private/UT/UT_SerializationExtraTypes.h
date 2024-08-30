#pragma once
#ifndef IS_UNREAL
#include "../../central_juce.h"
#endif

namespace UT
{
void serTest();

using SerChunkVersion = unsigned short;
using SerOptChunkId = unsigned char;
static const SerOptChunkId serOptChunkIdNone = 0;

class SerializationData;
void serializationDebugTraversal(SerializationData& data);

using SerAtomKinds = unsigned char;
static const SerAtomKinds eSerAtomKindNone = 0;
static const SerAtomKinds eSerAtomKindBool = 1;
static const SerAtomKinds eSerAtomKindChar = 2;
static const SerAtomKinds eSerAtomKindUnsignedChar = 3;
static const SerAtomKinds eSerAtomKindShort = 4;
static const SerAtomKinds eSerAtomKindUnsignedShort = 5;
static const SerAtomKinds eSerAtomKindInt = 6;
static const SerAtomKinds eSerAtomKindUnsignedInt = 7;
static const SerAtomKinds eSerAtomKindInt64 = 8;
static const SerAtomKinds eSerAtomKindUnsignedInt64 = 9;
static const SerAtomKinds eSerAtomKindFloat = 10;
static const SerAtomKinds eSerAtomKindDouble = 11;
static const SerAtomKinds eSerAtomKindVec2 = 12;
static const SerAtomKinds eSerAtomKindVec3 = 13;
static const SerAtomKinds eSerAtomKindVec4 = 14;
static const SerAtomKinds eSerAtomKindMat3 = 15;
static const SerAtomKinds eSerAtomKindMat4 = 16;
static const SerAtomKinds eSerAtomKindString = 17;
static const SerAtomKinds eSerAtomKindBuffer = 32;
static const SerAtomKinds eSerAtomKindGeneric = 33;
static const SerAtomKinds eSerAtomKindGenericVector = 34;
static const SerAtomKinds eSerAtomKindInterthreadId = 35;
static const SerAtomKinds eSerAtomKindQuaternion = 36;
static const SerAtomKinds eSerAtomKindSmallEnum = 37;
static const SerAtomKinds eSerAtomKindFloatVec3 = 38;
static const SerAtomKinds eSerAtomKindSerData = 39;
static const SerAtomKinds eSerAtomKindBufferVec = 40;
static const SerAtomKinds eSerAtomKindChunk = 64;
static const SerAtomKinds eSerAtomKindEncrypted = 65;
static const SerAtomKinds eSerAtomKindIntVec2 = 66;
static const SerAtomKinds eSerAtomKindIntVec3 = 67;

class CompatibilityInfos
{
public:
	CompatibilityInfos() = default;
	virtual ~CompatibilityInfos() = default;
};
}
