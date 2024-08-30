// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <any>
#include <variant>
#include "CoreMinimal.h"
#include "AV/AV_UnrealSerializationHelper.h"
#include "AV/AV_UnrealExtraTypes.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LevelStreaming.h"
#include "Cluster/IDisplayClusterClusterSyncObject.h"
#include "PXConnectBlueprintInterface.h"
#include "PXConnectSyncObject.h"
#include "PXConnectRootObjects.generated.h"

class IDisplayClusterGameManager;
class IDisplayClusterClusterManager;
class UPXConnectSyncObject;
struct FPropInfo;

typedef TArray<FString> propertyList;

static constexpr int eLevelToLoadDirty = 1;
static constexpr int eBlacklistDirty = 2;
static constexpr int eVisibilityMapDirty = 4;

const FString serPrefix(TEXT("RootObjctSync_"));
const FString serIdentifierLevel(TEXT("Level"));
const FString serIdentifierBlacklist(TEXT("Blacklist"));
const FString serIdentifierVisibilityMap(TEXT("VisibilityMap"));

typedef std::variant<FPXDataReceivedEventInt,
	FPXDataReceivedEventIntArray,
	FPXDataReceivedEventFloat,
	FPXDataReceivedEventFloatArray,
	FPXDataReceivedEventColor,
	FPXDataReceivedEventVec3d,
	FPXDataReceivedEventVec2d> dataReceivedVariant;

UCLASS()
class PIXERA_CONNECT_API UPXConnectRootObjects : public UObject, public IDisplayClusterClusterSyncObject
{
	GENERATED_BODY()

public:
	void BeginDestroy() override;
	void worldBeginPlay();
	AActor* getActorWithName(const FString& objectName);
	void loadSubStreamingLevels();
	void loadCurrentActors();
	void getAssets();
	void updateLayersFromActor(AActor* pActor);
	void applyBlacklistedLayers(const AV::BlacklistInfoMap& inInfoMap);
	void applyVisibility(const AV::VisibilityMap& visibilityMap);
	const TArray<ULevelStreaming*>& getAllLevelStreaming();
	const TMap<FString, AActor*>& getAllActors();
	void addKnownActor(AActor* pActor);
	void loadFromSerStruct(AV::UnrealSerializationHelper::UnrealWorldSerializationStruct* pWorldSerStruct);
	void loadOrCreateActorFromSerStruct(AV::UnrealSerializationHelper::UnrealEntitySerializationStruct* pSerStruct);
	void loadCameraFromSerStruct(UDisplayClusterICVFXCameraComponent* pCamComp, AV::UnrealSerializationHelper::UnrealEntityCineCameraSerializationStruct* pSerStruct);
	void overrideAttributesOfActor(AV::UnrealSerializationHelper::UnrealNodeSpecificOverrideStruct* pSerStruct);
	void setPxParentWorldDiff(unsigned long long diff);
	unsigned long long getPxParentWorldDiff();
	void sendWorldUpdate();
	void sendActorUpdate(AActor* pActor);
	void sendComponentUpdate(USceneComponent* pComp);
	float getWorldToMetersFactor();
	void loadLevel(const FName& levelName,bool forceLoad=false);
	UFUNCTION()
	void levelLoaded();
	UFUNCTION()
	void levelUnloaded();
#if !BELOW_5_1
	template<typename D,typename V>
	bool executeDelegate(const std::any& delegate,const std::any& value);
	void registerDataReceivedEvent(const std::any& eventDelegate,const FString& eventName);
	void triggerDataReceivedEvent(const FString& eventName,const std::any& data,AV::UnrealDataKind eDataKind,bool isArray);
#endif
	void registerEvent(const FPXTriggerEvent& pxEvent, const FString& eventName);
	void triggerEvent(const FString& eventName);
	const std::map<FString,FPXTriggerEvent>& getEventMap();
// Sync:
	bool IsActive() const override;
	FString GetSyncId() const override;
	bool IsDirty() const override;
	void ClearDirty() override;
	FString SerializeToString() const override;
	bool DeserializeFromString(const FString& ar) override;
	void createSyncObjectsForObject(UObject* pObject);;
	void createSyncObjectsForActor(AActor* pActor);
	void createAndAddSyncObject(const TArray<FName>& names,UObject* pObject,const PXConnectCustomPostSyncDeserializationFunc& updaetFunc=nullptr,const FName& customName=FName());
	bool syncObjectAlreadyCreated(const FName& syncObjectName);
	void clearSyncObjects();
	void getActorLayerNames(std::vector<std::string>& layersOut);
	bool getActorShouldBeInvisible(AActor* pActor);
	bool getActorVisibilityControlledByVisibilityMap(AActor* pActor);
	void removeSyncObject(UPXConnectSyncObject* pSyncObject);
	const FString& getNameOfLevelCurrentlyBeingLoaded();
protected:
	TArray<AActor*> getActorsWithLayerName(const FString& layerName);
	void applyVisibilityToActor(AActor* pActor,bool visible);
	FString getDataForIdentifier(const FString identifier,const FString& data);
	void deserializeBlackList(const FString& data);
	void deserializeVisibilityMap(const FString& data);
	unsigned long long m_pxWorldDiff;
	TMap<FString, AActor*> m_actors;
	TSet<FName> m_actorLayerNames;
	AV::BlacklistInfoMap m_nodeLayerBlacklist;
	AV::VisibilityMap m_nodeVisibilityMap;
	float m_worldToMetersFactor;
	TMap<AActor*, AV::UnrealSerializationHelper::UnrealNodeSpecificOverrideStruct> m_actorOverrides;
	TArray<ULevelStreaming*> m_streamLevels;
	// Package name of streaming level, will be set before level will be loaded
	FName m_levelToLoad;
	FString m_nameOfLevelCurrentlybeingLoaded;
	bool m_loadAfterwards;
	std::map<FString,FPXTriggerEvent> m_eventMap;
#if !BELOW_5_1
	std::map<FString, std::any> m_dataReceivedEventMap;
#endif
// Sync:
	//bool m_dirty = false;
	int m_dirtyFlag;
	FString m_syncId;
	IDisplayClusterGameManager* m_pGameManager = nullptr;
	IDisplayClusterClusterManager* m_pClusterManager = nullptr;
	// Lifecycle of sync objects will be handled by nDisplay after register() is called.
	// Therefore syncobjects in Array can be NULL and have to be checked!
	UPROPERTY(Transient)
	TArray<UPXConnectSyncObject*> m_syncObjects;
};