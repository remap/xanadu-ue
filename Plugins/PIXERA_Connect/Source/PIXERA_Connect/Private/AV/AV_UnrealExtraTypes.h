#pragma once
#ifndef IS_UNREAL
#else
#include "UE_stdafx.h"
#include "Dom/JsonObject.h"
#endif // !IS_UNREAL

#define BELOW_5_1 0

namespace UT
{
class SerializationContext;
}

namespace AV
{
enum UnrealActorTypes
{
	eUnrealActorTypeNone = 0,
	eUnrealActorTypeLight = 1,
	eUnrealActorTypeStaticMesh = 2,
	eUnrealActorTypePawn = 3,
	eUnrealActorTypeController = 4,
	eUnrealActorTypeCineCamera = 5,
	eUnrealActorTypeDisplayClusterRoot = 6
};

enum UnrealLightTypes
{
	eLightTypeNone = 0,
	eLightTypeLocal = 4,
	eLightTypePoint = 5,
	eLightTypeRect = 6,
	eLightTypeSpot = 7,
	eLightTypeDirectional = 8,
};

enum UnrealLightUnits
{
	eUnitUnitless = 0,
	eUnitCandelas = 1,
	eUnitLumens = 2
};

enum UnrealMobilityTypes
{
	eMobilityTypeStatic = 0,
	eMobilityTypeStationary = 1,
	eMobilityTypeMovable = 2
};

enum UnrealFocusMethod
{
	eFocusMethodDoNotOverride,
	eFocusMethodManual,
	eFocusMethodTracking,
	eFocusMethodDisable,
	eFocusMethodMAX,
};

static constexpr unsigned int unrealSerializationFlagBackgroundInstancesOnly = 8;
static constexpr unsigned int unrealSerializationFlagForegroundInstancesOnly = 9;

struct UnrealLevelStreaming
{
	std::string name;
	bool loaded = false;
	bool visible = false;
};

enum UnrealDataKind
{
	eUnrealDataKindNone = 0,
	eUnrealDataKindInt = 1,
	eUnrealDataKindFloat = 2,
	eUnrealDataKindColor = 3,
	eUnrealDataKindVec3d = 4,
	eUnrealDataKindVec2d = 5
};

static constexpr const char* blackListedInfoChunkerName = "BlackListedInfo";

struct BlacklistedInfo
{
	BlacklistedInfo();
#ifndef IS_UNREAL
	BlacklistedInfo(const string& inCameraName,const std::list<string>& inLayerNames);
	void serialize(UT::SerializationContext& ctx);

	string cameraName;
	std::list<string> layerNames;
#else
	BlacklistedInfo(const FString& inCamName,const TArray<FName>& inLayerNames);
	TSharedPtr<FJsonObject> serializeToJson() const;
	void deserializeFromJson(TSharedPtr<FJsonObject> pJson);
	void serialize(UT::SerializationContext& ctx);
	bool isVoid();

	FString cameraName;
	TArray<FName> layerNames;
#endif
};

#ifndef IS_UNREAL
typedef std::map<string, vector<BlacklistedInfo>> BlacklistInfoMap;
#else
typedef TMap<FString, TArray<AV::BlacklistedInfo>> BlacklistInfoMap;
#endif

static constexpr const char* visibilityMapChunkName = "VisibilityMap";

struct VisibilityInfo
{
#ifndef IS_UNREAL
	void serialize(UT::SerializationContext& ctx);
#else
	TSharedPtr<FJsonObject> serializeToJson() const;
	void deserializeFromJson(TSharedPtr<FJsonObject> pJson);
	void serialize(UT::SerializationContext& ctx);
#endif

#ifndef IS_UNREAL
	string name;
#else
	FString name;
#endif
	bool isLayer = false;
	bool visible = true;
};

#ifndef IS_UNREAL
#else
typedef TMap<FString, TArray<VisibilityInfo>> VisibilityMap;
#endif

}
