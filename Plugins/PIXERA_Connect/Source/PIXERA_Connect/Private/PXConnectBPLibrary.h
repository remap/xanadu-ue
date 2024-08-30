#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PXConnectBPLibrary.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PIXERA_CONNECT_API UPXConnectBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static void resetDataToSend();

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataFloat(FName dataName,float val,float& outVal);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataInt(FName dataName,int val,int& outVal);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataInt64(FName dataName,int64 val,int64& outVal);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataString(FName dataName,FString val,FString& outVal);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataName(FName dataName,FName val,FName& outVal);

	/*UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool sendDataSendStruct(FName dataName, int val, int& outVal);*/
};

