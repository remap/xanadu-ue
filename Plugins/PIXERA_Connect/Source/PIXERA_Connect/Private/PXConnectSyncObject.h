#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "UObject/NoExportTypes.h"
#include "Cluster/IDisplayClusterClusterSyncObject.h"
#include <vector>
#include <functional>
#include "PXConnectSyncObject.generated.h"

class IDisplayClusterGameManager;
class IDisplayClusterClusterManager;
class FProperty;
class FJsonObject;

enum PropertyTypes
{
	ePropertyTypeNone,
	ePropertyTypeNumeric,
	ePropertyTypeByte,
	ePropertyTypeInt8,
	ePropertyTypeInt16,
	ePropertyTypeInt,
	ePropertyTypeInt64,
	ePropertyTypeUInt16,
	ePropertyTypeUInt32,
	ePropertyTypeUInt64,
	ePropertyTypeFloat,
	ePropertyTypeDouble,
	ePropertyTypeBool,
	ePropertyTypeObjectBase,
	ePropertyTypeObject,
	ePropertyTypeObjectWeak,
	ePropertyTypeObjectLazy,
	ePropertyTypeObjectSoft,
	ePropertyTypeClass,
	ePropertyTypeClassSoft,
	ePropertyTypeInterface,
	ePropertyTypeName,
	ePropertyTypeString,
	ePropertyTypeArray,
	ePropertyTypeMap,
	ePropertyTypeSet,
	ePropertyTypeStruct,
	ePropertyTypeDelegate,
	ePropertyTypeDelegateMulticast,
	ePropertyTypeDelegateMulticastInline,
};

typedef TFunction<bool(UObject* pObject,FProperty* pProperty,TSharedPtr<FJsonObject> pJsonObject)> PXConnectCustomPostSyncDeserializationFunc;

class CachedProperty
{
public:
	CachedProperty(FProperty* pProp,UObject* pObject);
	~CachedProperty();
	void init(FProperty* pProp, UObject* pObject);
	bool isDirty(UObject* pObject) const;
	void clearDirty(UObject* pObject);
	void resetValue();
	FString serializeToStringBinary(UObject* pObject) const;
	FString serializeToStringJson(UObject* pObject) const;
	bool deserializeFromStringBinary(FString& data, UObject* pObject);
	bool deserializeFromStringJson(FString& data, UObject* pObject,const PXConnectCustomPostSyncDeserializationFunc& deSerFunc=nullptr);
	FProperty* getProperty();
protected:
	void updateValue(UObject* pObject);
	FProperty* m_pProperty = nullptr;
	void* m_pCachedData = nullptr;
	FString m_cachedSerData;
};

UCLASS()
class PIXERA_CONNECT_API UPXConnectSyncObject : public UObject, public IDisplayClusterClusterSyncObject
{
	GENERATED_BODY()
public:
	void init(UObject* pObject,const TArray<FName>& propNames,const PXConnectCustomPostSyncDeserializationFunc& deSerFunc=nullptr);
	void BeginDestroy() override;
	void unregister();
	bool IsActive() const override;
	FString GetSyncId() const override;
	bool IsDirty() const override;
	void ClearDirty() override;
	FString SerializeToString() const override;
	bool DeserializeFromString(const FString& ar) override;

protected:
	TArray<TUniquePtr<CachedProperty>> m_cachedProperties;
	
	UPROPERTY()
	UObject* m_pObject = nullptr;

	IDisplayClusterGameManager* m_pGameManager = nullptr;
	IDisplayClusterClusterManager* m_pClusterManager = nullptr;
	FString m_syncId;
	bool m_useJson = true;
	PXConnectCustomPostSyncDeserializationFunc m_customDeSerFunc;
};