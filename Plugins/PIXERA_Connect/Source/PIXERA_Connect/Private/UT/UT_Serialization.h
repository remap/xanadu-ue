#pragma once
#include "UT_SerializationContext.h"
#include "UT_SerializationConverter.h"
#include "UT_SerializationData.h"
#include "UT_SerializationChunker.h"
#ifndef IS_UNREAL
#include "UT_CopyableDestroyer.h"
#endif

namespace UT
{
template <class T>
void serGenericNext(SerializationConverter& conv,T& object)
{
	// Objects of arbitrary size destroy analyzability of serialization data.
	// If different sizes are desired in the future (only size four was used when the
	// static assert was introduced) then the serialization mechanism needs
	// to serialize a hint that indicates which size was actually used.
	static_assert (sizeof(T) == 4, "Generic objects must be four bytes in size.");
	SerializationData& data = conv.getData();
	if(conv.getIsWrite())
	{
		data.write(&eSerAtomKindGeneric, 1);
		data.write(&object, sizeof(T));
	}
	else
	{
		SerAtomKinds eReadKind = eSerAtomKindNone;
		data.read(&eReadKind, 1);
		if(eReadKind != eSerAtomKindGeneric)
		{
			data.appendToLog("Expected generic atom kind.\r\n");
		}
		data.read(&object, sizeof(T));
	}
}

template <class T>
void serGenericNext(SerializationConverter& conv,const T& object)
{
	static_assert (sizeof(T) == 4, "Generic objects must be four bytes in size.");
	SerializationData& data = conv.getData();
	if(conv.getIsWrite())
	{
		data.write(&eSerAtomKindGeneric, 1);
		data.write(&object, sizeof(T));
	}
	else
	{
		data.appendToLog("Can not read const generic data.\r\n");
	}
}
#ifndef IS_UNREAL
typedef CopyableDestroyer<SerializationData> CpDestSerData;
#endif
} // namespace_end
