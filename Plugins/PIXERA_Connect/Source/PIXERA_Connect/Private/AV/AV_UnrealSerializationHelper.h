#pragma once
#include "AV_UnrealExtraTypes.h"
#ifdef IS_UNREAL
#include "../UT/UT_SerializationContext.h"
#include "../UT/UT_SerializationData.h"
#include "Engine/Light.h"
#include "Engine/StaticMeshActor.h"
#include "CineCameraActor.h"
#include "DisplayClusterRootActor.h"
#include "Components/DisplayClusterICVFXCameraComponent.h"
#include "CineCameraComponent.h"
#include "PXConnectBlueprintInterface.h"
#include "UE_stdafx.h"
#else
#include "AV_ExtraTypes.h"
#include "AV_UnrealEntityLight.h"
#include "AV_UnrealEntityStaticMesh.h"
#include "AV_UnrealEntityDisplayClusterRoot.h"
#include "AV_UnrealEntityCineCamera.h"
#endif

//DECLARE_DELEGATE_RetVal(class UPXConnectMain*, FGetMainDelegate);
//FGetMainDelegate& getGetMainDelegate();

#ifdef IS_UNREAL
class UPXConnectRootObjects;
class ULevelStreaming;
#endif // IS_UNREAL


namespace AV
{

#ifdef IS_UNREAL
	
#else
class UnrealWorld;
class UnrealEntity;
#endif

namespace UnrealSerializationHelper
{
class UeSerStructFactory;

struct UnrealSerStruct
{
	UnrealSerStruct();
	virtual ~UnrealSerStruct();
	virtual void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true){return;};
	virtual void apply();
	UnrealSerStruct& operator-=(UnrealSerStruct& other);
	UnrealSerStruct& operator*=(UnrealSerStruct& other);
	UnrealSerStruct& operator*=(double factor);
	UnrealSerStruct& operator+=(UnrealSerStruct& other);
	virtual bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther);
};

struct UnrealNodeSpecificOverrideStruct : UnrealSerStruct
{
	UnrealNodeSpecificOverrideStruct();
#ifndef IS_UNREAL
	UnrealNodeSpecificOverrideStruct(UnrealEntity* pEntity);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true);
	bool hasChangesThatNeedInterpolation(UnrealSerStruct& other);

	std::string objectName;
	unsigned long long parentWorldInterthreadIdDiff;
	bool overrideVisibility;
	bool visibility;
};

struct UnrealVec3 : UnrealSerStruct
{
	UnrealVec3();
	UnrealVec3(float inX,float inY,float inZ);
#ifndef IS_UNREAL
	UnrealVec3(const mlVec3& inVec);
#else
	UnrealVec3(const FVector& inVec);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
#ifndef IS_UNREAL
	virtual mlVec3 asMlVec() const;
#else
	FVector asFvector() const;
#endif
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther) override;
	UnrealVec3& operator-=(UnrealVec3& other);
	UnrealVec3& operator*=(UnrealVec3& other);
	UnrealVec3& operator*=(double& factor);
	UnrealVec3& operator+=(UnrealVec3& other);
	bool operator==(UnrealVec3& other);
	bool operator!=(UnrealVec3& other);
	float x;
	float y;
	float z;
};

struct UnrealVec3Scale : UnrealVec3
{
	UnrealVec3Scale();
#ifndef IS_UNREAL
	using UnrealVec3::UnrealVec3;
#else
	using UnrealVec3::UnrealVec3;
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
};

//Struct for helping transferring Positional Data from Pixera to UE an back.
//Data will be converted to match the present coordinate System
struct UnrealVec3Pos : UnrealVec3
{
	UnrealVec3Pos();
#ifndef IS_UNREAL
	using UnrealVec3::UnrealVec3;
#else
	using UnrealVec3::UnrealVec3;
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
};

//Struct for helping transferring Rotation Data from Pixera to UE an back.
//Data will be converted to match the present coordinate System
struct UnrealVec3Rot : UnrealVec3
{
	UnrealVec3Rot();
#ifndef IS_UNREAL
	using UnrealVec3::UnrealVec3;
#else
	using UnrealVec3::UnrealVec3;
	UnrealVec3Rot(const FRotator& inRotator);
#endif
#ifndef IS_UNREAL
	mlVec3 asMlVec() const override;
#else
	FRotator asFRotator() const;
#endif
	void serialize(UT::SerializationContext& ctx, UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
};

struct UnrealColor : UnrealSerStruct
{
	UnrealColor();
	UnrealColor(unsigned int inR, unsigned int inG, unsigned int inB, unsigned int inA);
#ifndef IS_UNREAL
	UnrealColor(const miVec4& inColor);
#else
	UnrealColor(const FColor& inColor);
#endif
	void serialize(UT::SerializationContext& ctx, UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
#ifndef IS_UNREAL
	miVec4 asMiVec() const;
#else
	FColor asFColor() const;
#endif // !IS_UNREAL
	UnrealColor& operator-=(UnrealColor& other);
	UnrealColor& operator*=(UnrealColor& other);
	UnrealColor& operator*=(double factor);
	UnrealColor& operator+=(UnrealColor& other);
	bool operator==(UnrealColor& other);
	bool operator!=(UnrealColor& other);

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};

struct UnrealEntitySerializationStruct : UnrealSerStruct
{
	UnrealEntitySerializationStruct();
	~UnrealEntitySerializationStruct();
#ifndef IS_UNREAL
	UnrealEntitySerializationStruct(UnrealEntity* pEntity);
#else
	UnrealEntitySerializationStruct(AActor* pActor);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool isReferringToSameObject(UnrealEntitySerializationStruct* pOther);
	void apply() override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther);
	/*virtual UnrealEntitySerializationStruct* makeCopy();*/
	UnrealEntitySerializationStruct& operator-=(UnrealEntitySerializationStruct& other);
	UnrealEntitySerializationStruct& operator*=(UnrealEntitySerializationStruct& other);
	UnrealEntitySerializationStruct& operator*=(double& factor);
	UnrealEntitySerializationStruct& operator+=(UnrealEntitySerializationStruct& other);

	std::string objectName;
	UnrealVec3Pos position;
	UnrealVec3Rot rotation;
	UnrealVec3Scale scale;
	unsigned long long parentWorldInterthreadIdDiff;
	UnrealMobilityTypes eMobilityType;
	bool isVisible;
	std::string levelName;
	std::string folderPath;
	std::string displayName;
	std::vector<UnrealEntitySerializationStruct*> children;
};

struct UnrealEntityLightSerializationStruct : public UnrealEntitySerializationStruct
{
	UnrealEntityLightSerializationStruct();
#ifndef IS_UNREAL
	UnrealEntityLightSerializationStruct(UnrealEntityLight* pEntity);
#else
	UnrealEntityLightSerializationStruct(ALight* pLight);
#endif // !IS_UNREAL

	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther);
	/*UnrealEntityLightSerializationStruct* makeCopy() override;*/
	UnrealEntityLightSerializationStruct& operator-=(UnrealEntityLightSerializationStruct& other);
	UnrealEntityLightSerializationStruct& operator*=(UnrealEntityLightSerializationStruct& other);
	UnrealEntityLightSerializationStruct& operator*=(double factor);
	UnrealEntityLightSerializationStruct& operator+=(UnrealEntityLightSerializationStruct& other);


	UnrealLightTypes eLightType;
	float brightness;
	UnrealVec3 lightColor;
	float colorTemperature;
	bool useColorTemperature;
	//Directional Light
	int32 atmosphereSunLightIndex;
	//Local Light Comp
	float attenuationRadius;
	UnrealLightUnits eUnit;
	//Point Light
	bool useInverseSquaredFalloff;
	float lightFalloffExponent;
	float softSourceRadius;
	float sourceLength;
	float sourceRadius;
	//Spot Light
	float innerConeAngle;
	float outerConeAngle;
	//Rect Light
	float barnDoorAngle;
	float barnDoorLength;
	float sourceHeight;
	float sourceWidth;

};

struct UnrealFilmbackSettingsSerStruct : UnrealSerStruct
{
	UnrealFilmbackSettingsSerStruct();
#ifndef IS_UNREAL
	UnrealFilmbackSettingsSerStruct(UnrealEntityCineCamera* pEntity);
#else
	UnrealFilmbackSettingsSerStruct(const FCameraFilmbackSettings& settings);
	void asFCameraFilmbackSettings(FCameraFilmbackSettings& settings);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther) override;
	UnrealFilmbackSettingsSerStruct& operator-=(UnrealFilmbackSettingsSerStruct& other);
	UnrealFilmbackSettingsSerStruct& operator*=(UnrealFilmbackSettingsSerStruct& other);
	UnrealFilmbackSettingsSerStruct& operator*=(double factor);
	UnrealFilmbackSettingsSerStruct& operator+=(UnrealFilmbackSettingsSerStruct& other);
	float sensorWidth;
	float sensorHeight;
	// Not settable in Editor
	float sensorAspectRatio;
};

struct UnrealLensSettingsSerStruct : UnrealSerStruct
{
	UnrealLensSettingsSerStruct();
#ifndef IS_UNREAL
	UnrealLensSettingsSerStruct(UnrealEntityCineCamera* pEntity);
#else
	UnrealLensSettingsSerStruct(const FCameraLensSettings& settings);
	void asFCameraLensSettings(FCameraLensSettings& settings);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther) override;
	UnrealLensSettingsSerStruct& operator-=(UnrealLensSettingsSerStruct& other);
	UnrealLensSettingsSerStruct& operator*=(UnrealLensSettingsSerStruct& other);
	UnrealLensSettingsSerStruct& operator*=(double factor);
	UnrealLensSettingsSerStruct& operator+=(UnrealLensSettingsSerStruct& other);
	int diaphragmCount;
	float minFocalLength;
	float maxFocalLength;
	float minFStop;
	float maxFStop;
	// Not settable in Editor
	float minFocusDistance;
};

struct UnrealFocusTrackingSettingsSerStruct : UnrealSerStruct
{
	UnrealFocusTrackingSettingsSerStruct();
#ifndef IS_UNREAL
	UnrealFocusTrackingSettingsSerStruct(UnrealEntityCineCamera* pEntity);
#else
	UnrealFocusTrackingSettingsSerStruct(const FCameraTrackingFocusSettings& settings);
	void asFCameraTrackingFocusSettings(FCameraTrackingFocusSettings& settings);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	std::string entityName;
	UnrealVec3Pos relativeOffset;
};

struct UnrealFocusSettingsSerStruct : UnrealSerStruct
{
	UnrealFocusSettingsSerStruct();
#ifndef IS_UNREAL
	UnrealFocusSettingsSerStruct(UnrealEntityCineCamera* pEntity);
#else
	UnrealFocusSettingsSerStruct(const FCameraFocusSettings& settings);
	void asFCameraFocusSettings(FCameraFocusSettings& settings);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther) override;
	UnrealFocusSettingsSerStruct& operator-=(UnrealFocusSettingsSerStruct& other);
	UnrealFocusSettingsSerStruct& operator*=(UnrealFocusSettingsSerStruct& other);
	UnrealFocusSettingsSerStruct& operator*=(double factor);
	UnrealFocusSettingsSerStruct& operator+=(UnrealFocusSettingsSerStruct& other);
	UnrealFocusMethod eFocusMethod;
	bool drawDebugFocusPlane;
	bool smoothFocusChanges;
	float focusSmoothingInterpSpeed;
	UnrealColor debugPlaneColor;
	float focusOffset;
	float manualFocusDistance;
	UnrealFocusTrackingSettingsSerStruct trackingSettings;
};

struct UnrealEntityCineCameraSerializationStruct : UnrealEntitySerializationStruct
{
	UnrealEntityCineCameraSerializationStruct();
#ifndef IS_UNREAL
	UnrealEntityCineCameraSerializationStruct(UnrealEntityCineCamera* pEntity);
#else
	UnrealEntityCineCameraSerializationStruct(UDisplayClusterICVFXCameraComponent* pComp);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther) override;
	UnrealEntityCineCameraSerializationStruct& operator-=(UnrealEntityCineCameraSerializationStruct& other);
	UnrealEntityCineCameraSerializationStruct& operator*=(UnrealEntityCineCameraSerializationStruct& other);
	UnrealEntityCineCameraSerializationStruct& operator*=(double factor);
	UnrealEntityCineCameraSerializationStruct& operator+=(UnrealEntityCineCameraSerializationStruct& other);
	std::string parentName;
	std::string currentFilmbackPresetName;
	std::vector<std::string> filmbackPresetNames;
	UnrealFilmbackSettingsSerStruct filmbackSettings;
	std::string currentLensPresetName;
	std::vector<std::string> lensPresetNames;
	UnrealLensSettingsSerStruct lensSettings;
	UnrealFocusSettingsSerStruct focusSettings;
	float currentAperture;
	float currentFocalLength;
	// Not settable in Editor
	float currentFocusDistance;
	float currentHorFov;
};

struct UnrealEntityDisplayClusterRootSerializationStruct : UnrealEntitySerializationStruct
{
	UnrealEntityDisplayClusterRootSerializationStruct();
#ifndef IS_UNREAL
	UnrealEntityDisplayClusterRootSerializationStruct(UnrealEntityDisplayClusterRoot* pRoot);
#else
	UnrealEntityDisplayClusterRootSerializationStruct(ADisplayClusterRootActor* pActor);
#endif
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
};

struct UnrealEntityStaticMeshSerializationStruct : UnrealEntitySerializationStruct
{
	UnrealEntityStaticMeshSerializationStruct();
#ifndef IS_UNREAL
	UnrealEntityStaticMeshSerializationStruct(UnrealEntityStaticMesh* pEntity);
#else
	UnrealEntityStaticMeshSerializationStruct(AStaticMeshActor* pStaticMesh);
#endif

	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
};

struct UnrealLevelStreamingSerializationStruct : UnrealSerStruct
{
	UnrealLevelStreamingSerializationStruct();
#ifndef IS_UNREAL
	UnrealLevelStreamingSerializationStruct(UnrealLevelStreaming* pLevelStreaming);
#else
	UnrealLevelStreamingSerializationStruct(ULevelStreaming* pLevelStreaming);
#endif
	~UnrealLevelStreamingSerializationStruct();
	void serialize(UT::SerializationContext& ctx, UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	std::string levelName;
	bool isLoaded;
	std::string loadedLevelName;
};

struct UnrealWorldSerializationStruct : UnrealSerStruct
{
	UnrealWorldSerializationStruct();
#ifndef IS_UNREAL
	UnrealWorldSerializationStruct(UnrealWorld* pWorld);
#else
	UnrealWorldSerializationStruct(UPXConnectRootObjects* pRootObjects);
#endif
	~UnrealWorldSerializationStruct();
	void serialize(UT::SerializationContext& ctx,UeSerStructFactory* pFactory=nullptr,bool apply=true) override;
	bool hasChangesWhichRequireInterpolation(UnrealSerStruct* pOther);
	std::string worldName;
	unsigned long long worldInterthreadIdDiff;
	std::vector<UnrealEntitySerializationStruct*> childEntities;
	std::vector<UnrealLevelStreamingSerializationStruct*> streamingLevels;
	std::vector<std::string> eventTrigger;
	std::string nameOfLevelCurrentlyBeingLoaded;
	std::vector<std::string> actorLayers;
};

template <class Base>
class UeSerStructInstantiatorBase
{
public:
	virtual Base* create()
	{
		return nullptr;
	}
};

template <class Base,class Derived>
class UeSerStructInstantiator : public UeSerStructInstantiatorBase<Base>
{
public:
	Base* create() override
	{
		return new Derived();
	}
};

class UeInstNameComp
{
public:
	bool operator()(const char* pA, const char* pB) const { return strcmp(pA, pB) < 0; };
};

template <class Base>
using UeStructInstatiatorMap = std::map <const char*, UeSerStructInstantiatorBase<Base>*, UeInstNameComp>;

typedef UeSerStructInstantiatorBase<UnrealSerStruct> UeSerStructInst;
typedef UeStructInstatiatorMap<UnrealSerStruct> UeSerStructInstMap;
class UeSerStructFactory
{
public:
	UeSerStructFactory();
	~UeSerStructFactory();
	static UeSerStructFactory& instance();
	UnrealSerStruct* create(const char* pName);
protected:
	void addInstatiator(const char* pName,UeSerStructInst* pInst);
	UeSerStructInstMap m_instMap;
};

UnrealSerStruct* deserializeNetworkPacket(UT::SerializationContext& ctx,bool apply);
#ifdef IS_UNREAL
void serializeAndSend(UnrealSerStruct* pSerStruct);
UnrealEntitySerializationStruct* getSerStructForActorWithName(const FString& actorName);
UnrealEntitySerializationStruct* getSerStructForActor(AActor* pActor);
UnrealEntitySerializationStruct* getSerStructForComponent(USceneComponent* pComp);
#endif
#ifndef IS_UNREAL
UnrealEntity* createEntityFromSerStruct(UnrealEntitySerializationStruct* pSerStruct,bool doLoad=true);
#endif
}



}

