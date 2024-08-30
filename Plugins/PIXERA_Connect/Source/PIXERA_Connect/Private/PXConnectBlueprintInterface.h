#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
//#include "VectorTypes.h"
#include "PXConnectBlueprintInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FPXTriggerEvent);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventInt, int, intVal);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventFloat, float, floatVal);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventIntArray, TArray<int>, intArray);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventFloatArray, TArray<float>, floatArray);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventVec3d, FVector, vecVal);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventVec2d, FVector2D, vecVal);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPXDataReceivedEventColor, FColor, vecCol);

UCLASS()
class PIXERA_CONNECT_API UPXConnectBlueprintInterface : public UObject
{
	GENERATED_BODY()

public:

// Can't use preprocessor blocks here, comment out when compiling for any version belo 5.1
	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedInt(const FPXDataReceivedEventInt& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedFloat(const FPXDataReceivedEventFloat& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedIntArray(const FPXDataReceivedEventIntArray& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedFloatArray(const FPXDataReceivedEventFloatArray& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedVec3d(const FPXDataReceivedEventVec3d& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedVec2d(const FPXDataReceivedEventVec2d& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEventDataReceivedColor(const FPXDataReceivedEventColor& pxEvent,const FString& eventName);
// till here

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void registerEvent(const FPXTriggerEvent& pxEvent,const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void triggerEventWithRegisteredName(const FString& eventName);

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void sendDataInt(const TArray<int>& data,const FString& dataName=FString("MyData"));

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void sendDataFloat(const TArray<float>& data,const FString& dataName=FString("MyData"));

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void sendDataColor(FColor color,const FString& dataName=FString("MyColor"));

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void sendDataVector(FVector vec,const FString& dataName=FString("MyVec"));

	UFUNCTION(BlueprintCallable, Category = "Pixera")
	static void sendDataVector2D(FVector2D vec, const FString& dataName = FString("MyVec"));
};