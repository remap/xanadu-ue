#pragma once
#include "UT_SerializationExtraTypes.h"
#ifdef IS_UNREAL
#include "UE_stdafx.h"
#endif
namespace UT
{
class SerializationConverter;
class InterthreadIdBank;
class SerializationContext
{
public:
	SerializationContext(SerializationConverter& cnv);
	~SerializationContext();
	SerializationConverter& converter;
	InterthreadIdBank* pIdBank;
	bool allowIdRegistration;
	bool includeChildren;
	bool isForPersistence;
	bool isForCopy;
	bool isForBundling;
	bool writeRelativePaths;
	unique_ptr<string> pPersistenceDir;
	bool isForAutoSave;
};

}
