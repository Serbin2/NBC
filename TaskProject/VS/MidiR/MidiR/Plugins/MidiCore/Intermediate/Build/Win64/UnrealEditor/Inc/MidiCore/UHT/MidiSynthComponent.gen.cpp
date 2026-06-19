// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MidiCore/Public/MidiSynthComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMidiSynthComponent() {}

// Begin Cross Module References
AUDIOMIXER_API UClass* Z_Construct_UClass_USynthComponent();
MIDICORE_API UClass* Z_Construct_UClass_UMidiFileAsset_NoRegister();
MIDICORE_API UClass* Z_Construct_UClass_UMidiSynthComponent();
MIDICORE_API UClass* Z_Construct_UClass_UMidiSynthComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_MidiCore();
// End Cross Module References

// Begin Class UMidiSynthComponent Function GetDurationSeconds
struct Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics
{
	struct MidiSynthComponent_eventGetDurationSeconds_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventGetDurationSeconds_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "GetDurationSeconds", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::MidiSynthComponent_eventGetDurationSeconds_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::MidiSynthComponent_eventGetDurationSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execGetDurationSeconds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetDurationSeconds();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function GetDurationSeconds

// Begin Class UMidiSynthComponent Function GetPlayPositionSeconds
struct Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics
{
	struct MidiSynthComponent_eventGetPlayPositionSeconds_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x98\x84\xec\x9e\xac \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98(\xec\xb4\x88) \xe2\x80\x94 \xec\x8b\x9c\xea\xb0\x81\xed\x99\x94(\xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4) \xeb\x8f\x99\xea\xb8\xb0\xed\x99\x94\xec\x9a\xa9\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x98\x84\xec\x9e\xac \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98(\xec\xb4\x88) \xe2\x80\x94 \xec\x8b\x9c\xea\xb0\x81\xed\x99\x94(\xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4) \xeb\x8f\x99\xea\xb8\xb0\xed\x99\x94\xec\x9a\xa9" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventGetPlayPositionSeconds_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "GetPlayPositionSeconds", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::MidiSynthComponent_eventGetPlayPositionSeconds_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::MidiSynthComponent_eventGetPlayPositionSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execGetPlayPositionSeconds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetPlayPositionSeconds();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function GetPlayPositionSeconds

// Begin Class UMidiSynthComponent Function IsChannelMuted
struct Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics
{
	struct MidiSynthComponent_eventIsChannelMuted_Parms
	{
		int32 Channel;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Channel;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_Channel = { "Channel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventIsChannelMuted_Parms, Channel), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MidiSynthComponent_eventIsChannelMuted_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiSynthComponent_eventIsChannelMuted_Parms), &Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_Channel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "IsChannelMuted", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::MidiSynthComponent_eventIsChannelMuted_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::MidiSynthComponent_eventIsChannelMuted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execIsChannelMuted)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Channel);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsChannelMuted(Z_Param_Channel);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function IsChannelMuted

// Begin Class UMidiSynthComponent Function IsPlayingMidi
struct Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics
{
	struct MidiSynthComponent_eventIsPlayingMidi_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MidiSynthComponent_eventIsPlayingMidi_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiSynthComponent_eventIsPlayingMidi_Parms), &Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "IsPlayingMidi", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::MidiSynthComponent_eventIsPlayingMidi_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::MidiSynthComponent_eventIsPlayingMidi_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execIsPlayingMidi)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsPlayingMidi();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function IsPlayingMidi

// Begin Class UMidiSynthComponent Function PauseMidi
struct Z_Construct_UFunction_UMidiSynthComponent_PauseMidi_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xa0\x95\xec\xa7\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xa0\x95\xec\xa7\x80" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_PauseMidi_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "PauseMidi", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_PauseMidi_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_PauseMidi_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_PauseMidi()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_PauseMidi_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execPauseMidi)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PauseMidi();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function PauseMidi

// Begin Class UMidiSynthComponent Function PlayMidi
struct Z_Construct_UFunction_UMidiSynthComponent_PlayMidi_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe2\x94\x80\xe2\x94\x80 \xec\xbb\xa8\xed\x8a\xb8\xeb\xa1\xa4(\xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8) \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe2\x94\x80\xe2\x94\x80 \xec\xbb\xa8\xed\x8a\xb8\xeb\xa1\xa4(\xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8) \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_PlayMidi_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "PlayMidi", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_PlayMidi_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_PlayMidi_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_PlayMidi()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_PlayMidi_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execPlayMidi)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayMidi();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function PlayMidi

// Begin Class UMidiSynthComponent Function PreviewPlay
struct Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Midi|Preview" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90 \xeb\xb2\x84\xed\x8a\xbc \xe2\x80\x94 \xec\x97\x90\xeb\x94\x94\xed\x84\xb0\xec\x97\x90\xec\x84\x9c PIE \xec\x97\x86\xec\x9d\xb4 \xeb\xaf\xb8\xeb\xa6\xac\xeb\x93\xa3\xea\xb8\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90 \xeb\xb2\x84\xed\x8a\xbc \xe2\x80\x94 \xec\x97\x90\xeb\x94\x94\xed\x84\xb0\xec\x97\x90\xec\x84\x9c PIE \xec\x97\x86\xec\x9d\xb4 \xeb\xaf\xb8\xeb\xa6\xac\xeb\x93\xa3\xea\xb8\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "PreviewPlay", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execPreviewPlay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PreviewPlay();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function PreviewPlay

// Begin Class UMidiSynthComponent Function PreviewStop
struct Z_Construct_UFunction_UMidiSynthComponent_PreviewStop_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Midi|Preview" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_PreviewStop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "PreviewStop", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_PreviewStop_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_PreviewStop_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_PreviewStop()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_PreviewStop_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execPreviewStop)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PreviewStop();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function PreviewStop

// Begin Class UMidiSynthComponent Function ResumeMidi
struct Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9d\xbc\xec\x8b\x9c\xec\xa0\x95\xec\xa7\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9d\xbc\xec\x8b\x9c\xec\xa0\x95\xec\xa7\x80" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "ResumeMidi", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execResumeMidi)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResumeMidi();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function ResumeMidi

// Begin Class UMidiSynthComponent Function SeekSeconds
struct Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics
{
	struct MidiSynthComponent_eventSeekSeconds_Parms
	{
		float Seconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xea\xb0\x9c\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xea\xb0\x9c" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Seconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::NewProp_Seconds = { "Seconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventSeekSeconds_Parms, Seconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::NewProp_Seconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SeekSeconds", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::MidiSynthComponent_eventSeekSeconds_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::MidiSynthComponent_eventSeekSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSeekSeconds)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Seconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SeekSeconds(Z_Param_Seconds);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SeekSeconds

// Begin Class UMidiSynthComponent Function SetChannelMute
struct Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics
{
	struct MidiSynthComponent_eventSetChannelMute_Parms
	{
		int32 Channel;
		bool bMute;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Channel;
	static void NewProp_bMute_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMute;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_Channel = { "Channel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventSetChannelMute_Parms, Channel), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_bMute_SetBit(void* Obj)
{
	((MidiSynthComponent_eventSetChannelMute_Parms*)Obj)->bMute = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_bMute = { "bMute", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiSynthComponent_eventSetChannelMute_Parms), &Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_bMute_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_Channel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::NewProp_bMute,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SetChannelMute", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::MidiSynthComponent_eventSetChannelMute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::MidiSynthComponent_eventSetChannelMute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSetChannelMute)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Channel);
	P_GET_UBOOL(Z_Param_bMute);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetChannelMute(Z_Param_Channel,Z_Param_bMute);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SetChannelMute

// Begin Class UMidiSynthComponent Function SetGainLevel
struct Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics
{
	struct MidiSynthComponent_eventSetGainLevel_Parms
	{
		float InGain;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InGain;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::NewProp_InGain = { "InGain", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventSetGainLevel_Parms, InGain), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::NewProp_InGain,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SetGainLevel", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::MidiSynthComponent_eventSetGainLevel_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::MidiSynthComponent_eventSetGainLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSetGainLevel)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InGain);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetGainLevel(Z_Param_InGain);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SetGainLevel

// Begin Class UMidiSynthComponent Function SetLoop
struct Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics
{
	struct MidiSynthComponent_eventSetLoop_Parms
	{
		bool bInLoop;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xb0\x98\xec\x9d\x8c -24~24\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xb0\x98\xec\x9d\x8c -24~24" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bInLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInLoop;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::NewProp_bInLoop_SetBit(void* Obj)
{
	((MidiSynthComponent_eventSetLoop_Parms*)Obj)->bInLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::NewProp_bInLoop = { "bInLoop", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiSynthComponent_eventSetLoop_Parms), &Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::NewProp_bInLoop_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::NewProp_bInLoop,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SetLoop", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::MidiSynthComponent_eventSetLoop_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::MidiSynthComponent_eventSetLoop_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SetLoop()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SetLoop_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSetLoop)
{
	P_GET_UBOOL(Z_Param_bInLoop);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetLoop(Z_Param_bInLoop);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SetLoop

// Begin Class UMidiSynthComponent Function SetPlaybackSpeed
struct Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics
{
	struct MidiSynthComponent_eventSetPlaybackSpeed_Parms
	{
		float Speed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventSetPlaybackSpeed_Parms, Speed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::NewProp_Speed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SetPlaybackSpeed", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::MidiSynthComponent_eventSetPlaybackSpeed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::MidiSynthComponent_eventSetPlaybackSpeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSetPlaybackSpeed)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Speed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetPlaybackSpeed(Z_Param_Speed);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SetPlaybackSpeed

// Begin Class UMidiSynthComponent Function SetTranspose
struct Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics
{
	struct MidiSynthComponent_eventSetTranspose_Parms
	{
		int32 Semitones;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Semitones;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::NewProp_Semitones = { "Semitones", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventSetTranspose_Parms, Semitones), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::NewProp_Semitones,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "SetTranspose", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::MidiSynthComponent_eventSetTranspose_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::MidiSynthComponent_eventSetTranspose_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_SetTranspose()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_SetTranspose_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execSetTranspose)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Semitones);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetTranspose(Z_Param_Semitones);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function SetTranspose

// Begin Class UMidiSynthComponent Function StopMidi
struct Z_Construct_UFunction_UMidiSynthComponent_StopMidi_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xb2\x98\xec\x9d\x8c\xeb\xb6\x80\xed\x84\xb0 \xec\x9e\xac\xec\x83\x9d\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xb2\x98\xec\x9d\x8c\xeb\xb6\x80\xed\x84\xb0 \xec\x9e\xac\xec\x83\x9d" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_StopMidi_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "StopMidi", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_StopMidi_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_StopMidi_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMidiSynthComponent_StopMidi()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_StopMidi_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execStopMidi)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopMidi();
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function StopMidi

// Begin Class UMidiSynthComponent Function ToggleChannelMute
struct Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics
{
	struct MidiSynthComponent_eventToggleChannelMute_Parms
	{
		int32 Channel;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Channel 0~15\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Channel 0~15" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Channel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::NewProp_Channel = { "Channel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiSynthComponent_eventToggleChannelMute_Parms, Channel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::NewProp_Channel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiSynthComponent, nullptr, "ToggleChannelMute", nullptr, nullptr, Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::MidiSynthComponent_eventToggleChannelMute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::MidiSynthComponent_eventToggleChannelMute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiSynthComponent::execToggleChannelMute)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Channel);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleChannelMute(Z_Param_Channel);
	P_NATIVE_END;
}
// End Class UMidiSynthComponent Function ToggleChannelMute

// Begin Class UMidiSynthComponent
void UMidiSynthComponent::StaticRegisterNativesUMidiSynthComponent()
{
	UClass* Class = UMidiSynthComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetDurationSeconds", &UMidiSynthComponent::execGetDurationSeconds },
		{ "GetPlayPositionSeconds", &UMidiSynthComponent::execGetPlayPositionSeconds },
		{ "IsChannelMuted", &UMidiSynthComponent::execIsChannelMuted },
		{ "IsPlayingMidi", &UMidiSynthComponent::execIsPlayingMidi },
		{ "PauseMidi", &UMidiSynthComponent::execPauseMidi },
		{ "PlayMidi", &UMidiSynthComponent::execPlayMidi },
		{ "PreviewPlay", &UMidiSynthComponent::execPreviewPlay },
		{ "PreviewStop", &UMidiSynthComponent::execPreviewStop },
		{ "ResumeMidi", &UMidiSynthComponent::execResumeMidi },
		{ "SeekSeconds", &UMidiSynthComponent::execSeekSeconds },
		{ "SetChannelMute", &UMidiSynthComponent::execSetChannelMute },
		{ "SetGainLevel", &UMidiSynthComponent::execSetGainLevel },
		{ "SetLoop", &UMidiSynthComponent::execSetLoop },
		{ "SetPlaybackSpeed", &UMidiSynthComponent::execSetPlaybackSpeed },
		{ "SetTranspose", &UMidiSynthComponent::execSetTranspose },
		{ "StopMidi", &UMidiSynthComponent::execStopMidi },
		{ "ToggleChannelMute", &UMidiSynthComponent::execToggleChannelMute },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMidiSynthComponent);
UClass* Z_Construct_UClass_UMidiSynthComponent_NoRegister()
{
	return UMidiSynthComponent::StaticClass();
}
struct Z_Construct_UClass_UMidiSynthComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n// MIDI \xec\x8b\xa0\xeb\x94\x94\xec\x82\xac\xec\x9d\xb4\xec\xa0\x80 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\n//\n// \xed\x8c\x8c\xec\x84\x9c(CMidi)\xea\xb0\x80 \xeb\xa7\x8c\xeb\x93\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\xeb\xa5\xbc \xec\x8b\x9c\xea\xb0\x81\xec\x88\x9c\xec\x9c\xbc\xeb\xa1\x9c \xed\x8f\x89\xed\x83\x84\xed\x99\x94\xed\x95\xb4 \xeb\x91\x90\xea\xb3\xa0, UE \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4 \xeb\xa0\x8c\xeb\x8d\x94 \xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c\xec\x97\x90\xec\x84\x9c\n// FluidSynth(\xec\x82\xac\xec\x9a\xb4\xeb\x93\x9c\xed\x8f\xb0\xed\x8a\xb8)\xeb\xa1\x9c \xec\xa7\x81\xec\xa0\x91 \xed\x95\xa9\xec\x84\xb1\xed\x95\xb4 USynthComponent \xeb\xa1\x9c \xec\xb6\x9c\xeb\xa0\xa5\xed\x95\x9c\xeb\x8b\xa4.\n//  - \xec\xbd\x98\xec\x86\x94\xed\x8c\x90 MidiPlayer \xec\x9d\x98 \xed\x8f\x89\xed\x83\x84\xed\x99\x94/\xeb\x94\x94\xec\x8a\xa4\xed\x8c\xa8\xec\xb9\x98/\xed\x83\x90\xec\x83\x89(chase) \xeb\xa1\x9c\xec\xa7\x81\xec\x9d\x84 \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4 \xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c \xeb\xaa\xa8\xeb\x8d\xb8\xeb\xa1\x9c \xec\x98\xae\xea\xb9\x80.\n//  - \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98/\xeb\xb0\xb0\xec\x86\x8d/\xec\x9d\xbc\xec\x8b\x9c\xec\xa0\x95\xec\xa7\x80/\xed\x83\x90\xec\x83\x89\xec\x9d\x80 \xea\xb2\x8c\xec\x9e\x84\xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c \xe2\x86\x92 \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c\xeb\xa5\xbc atomic \xec\x9c\xbc\xeb\xa1\x9c \xec\xa0\x84\xeb\x8b\xac.\n//\n// \xec\x82\xac\xec\x9a\xa9: \xec\x95\xa1\xed\x84\xb0\xec\x97\x90 \xec\x9d\xb4 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xeb\xa5\xbc \xeb\xb6\x99\xec\x9d\xb4\xea\xb3\xa0 MidiFilePath/SoundFontPath \xeb\xa5\xbc \xec\xa7\x80\xec\xa0\x95 \xe2\x86\x92 PlayMidi().\n// \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n" },
#endif
		{ "HideCategories", "Object ActorComponent Physics Rendering Mobility LOD Trigger PhysicsVolume" },
		{ "IncludePath", "MidiSynthComponent.h" },
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\nMIDI \xec\x8b\xa0\xeb\x94\x94\xec\x82\xac\xec\x9d\xb4\xec\xa0\x80 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\n\n\xed\x8c\x8c\xec\x84\x9c(CMidi)\xea\xb0\x80 \xeb\xa7\x8c\xeb\x93\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\xeb\xa5\xbc \xec\x8b\x9c\xea\xb0\x81\xec\x88\x9c\xec\x9c\xbc\xeb\xa1\x9c \xed\x8f\x89\xed\x83\x84\xed\x99\x94\xed\x95\xb4 \xeb\x91\x90\xea\xb3\xa0, UE \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4 \xeb\xa0\x8c\xeb\x8d\x94 \xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c\xec\x97\x90\xec\x84\x9c\nFluidSynth(\xec\x82\xac\xec\x9a\xb4\xeb\x93\x9c\xed\x8f\xb0\xed\x8a\xb8)\xeb\xa1\x9c \xec\xa7\x81\xec\xa0\x91 \xed\x95\xa9\xec\x84\xb1\xed\x95\xb4 USynthComponent \xeb\xa1\x9c \xec\xb6\x9c\xeb\xa0\xa5\xed\x95\x9c\xeb\x8b\xa4.\n - \xec\xbd\x98\xec\x86\x94\xed\x8c\x90 MidiPlayer \xec\x9d\x98 \xed\x8f\x89\xed\x83\x84\xed\x99\x94/\xeb\x94\x94\xec\x8a\xa4\xed\x8c\xa8\xec\xb9\x98/\xed\x83\x90\xec\x83\x89(chase) \xeb\xa1\x9c\xec\xa7\x81\xec\x9d\x84 \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4 \xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c \xeb\xaa\xa8\xeb\x8d\xb8\xeb\xa1\x9c \xec\x98\xae\xea\xb9\x80.\n - \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98/\xeb\xb0\xb0\xec\x86\x8d/\xec\x9d\xbc\xec\x8b\x9c\xec\xa0\x95\xec\xa7\x80/\xed\x83\x90\xec\x83\x89\xec\x9d\x80 \xea\xb2\x8c\xec\x9e\x84\xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c \xe2\x86\x92 \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xec\x8a\xa4\xeb\xa0\x88\xeb\x93\x9c\xeb\xa5\xbc atomic \xec\x9c\xbc\xeb\xa1\x9c \xec\xa0\x84\xeb\x8b\xac.\n\n\xec\x82\xac\xec\x9a\xa9: \xec\x95\xa1\xed\x84\xb0\xec\x97\x90 \xec\x9d\xb4 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xeb\xa5\xbc \xeb\xb6\x99\xec\x9d\xb4\xea\xb3\xa0 MidiFilePath/SoundFontPath \xeb\xa5\xbc \xec\xa7\x80\xec\xa0\x95 \xe2\x86\x92 PlayMidi().\n\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidiAsset_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b(\xec\xa7\x80\xec\xa0\x95\xeb\x90\x98\xeb\xa9\xb4 \xec\x95\x84\xeb\x9e\x98 MidiFilePath \xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9a\xb0\xec\x84\xa0)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b(\xec\xa7\x80\xec\xa0\x95\xeb\x90\x98\xeb\xa9\xb4 \xec\x95\x84\xeb\x9e\x98 MidiFilePath \xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9a\xb0\xec\x84\xa0)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidiFilePath_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x83\x9d\xed\x95\xa0 .mid \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80). MidiAsset \xec\x9d\xb4 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9.\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x83\x9d\xed\x95\xa0 .mid \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80). MidiAsset \xec\x9d\xb4 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundFontPath_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x82\xac\xec\x9a\xb4\xeb\x93\x9c\xed\x8f\xb0\xed\x8a\xb8 .sf2 \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x82\xac\xec\x9a\xb4\xeb\x93\x9c\xed\x8f\xb0\xed\x8a\xb8 .sf2 \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gain_MetaData[] = {
		{ "Category", "Midi" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa7\x88\xec\x8a\xa4\xed\x84\xb0 \xea\xb2\x8c\xec\x9d\xb8 0~1 (FluidSynth \xea\xb8\xb0\xeb\xb3\xb8 0.2)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa7\x88\xec\x8a\xa4\xed\x84\xb0 \xea\xb2\x8c\xec\x9d\xb8 0~1 (FluidSynth \xea\xb8\xb0\xeb\xb3\xb8 0.2)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlaybackSpeed_MetaData[] = {
		{ "Category", "Midi" },
		{ "ClampMax", "4.0" },
		{ "ClampMin", "0.25" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x83\x9d \xeb\xb0\xb0\xec\x86\x8d (0.25 ~ 4.0)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x83\x9d \xeb\xb0\xb0\xec\x86\x8d (0.25 ~ 4.0)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transpose_MetaData[] = {
		{ "Category", "Midi" },
		{ "ClampMax", "24" },
		{ "ClampMin", "-24" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xa1\xb0\xec\x98\xae\xea\xb9\x80(\xeb\xb0\x98\xec\x9d\x8c \xeb\x8b\xa8\xec\x9c\x84, -24~24). \xeb\x93\x9c\xeb\x9f\xbc \xec\xb1\x84\xeb\x84\x90(10)\xec\x9d\x80 \xec\xa0\x9c\xec\x99\xb8\xeb\x90\x9c\xeb\x8b\xa4.\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xa1\xb0\xec\x98\xae\xea\xb9\x80(\xeb\xb0\x98\xec\x9d\x8c \xeb\x8b\xa8\xec\x9c\x84, -24~24). \xeb\x93\x9c\xeb\x9f\xbc \xec\xb1\x84\xeb\x84\x90(10)\xec\x9d\x80 \xec\xa0\x9c\xec\x99\xb8\xeb\x90\x9c\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLoop_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xea\xb3\xa1 \xeb\x81\x9d\xec\x97\x90\xec\x84\x9c \xec\xb2\x98\xec\x9d\x8c\xeb\xb6\x80\xed\x84\xb0 \xeb\xb0\x98\xeb\xb3\xb5\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xea\xb3\xa1 \xeb\x81\x9d\xec\x97\x90\xec\x84\x9c \xec\xb2\x98\xec\x9d\x8c\xeb\xb6\x80\xed\x84\xb0 \xeb\xb0\x98\xeb\xb3\xb5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoPlayOnBeginPlay_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// BeginPlay \xec\x97\x90\xec\x84\x9c \xec\x9e\x90\xeb\x8f\x99 \xec\x9e\xac\xec\x83\x9d\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiSynthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BeginPlay \xec\x97\x90\xec\x84\x9c \xec\x9e\x90\xeb\x8f\x99 \xec\x9e\xac\xec\x83\x9d" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MidiAsset;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MidiFilePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SoundFontPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Gain;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaybackSpeed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Transpose;
	static void NewProp_bLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLoop;
	static void NewProp_bAutoPlayOnBeginPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoPlayOnBeginPlay;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMidiSynthComponent_GetDurationSeconds, "GetDurationSeconds" }, // 3895548315
		{ &Z_Construct_UFunction_UMidiSynthComponent_GetPlayPositionSeconds, "GetPlayPositionSeconds" }, // 3022816955
		{ &Z_Construct_UFunction_UMidiSynthComponent_IsChannelMuted, "IsChannelMuted" }, // 923444699
		{ &Z_Construct_UFunction_UMidiSynthComponent_IsPlayingMidi, "IsPlayingMidi" }, // 4185109237
		{ &Z_Construct_UFunction_UMidiSynthComponent_PauseMidi, "PauseMidi" }, // 3578013575
		{ &Z_Construct_UFunction_UMidiSynthComponent_PlayMidi, "PlayMidi" }, // 2802333328
		{ &Z_Construct_UFunction_UMidiSynthComponent_PreviewPlay, "PreviewPlay" }, // 2793964725
		{ &Z_Construct_UFunction_UMidiSynthComponent_PreviewStop, "PreviewStop" }, // 218606786
		{ &Z_Construct_UFunction_UMidiSynthComponent_ResumeMidi, "ResumeMidi" }, // 951368340
		{ &Z_Construct_UFunction_UMidiSynthComponent_SeekSeconds, "SeekSeconds" }, // 469282775
		{ &Z_Construct_UFunction_UMidiSynthComponent_SetChannelMute, "SetChannelMute" }, // 2984737024
		{ &Z_Construct_UFunction_UMidiSynthComponent_SetGainLevel, "SetGainLevel" }, // 1957613038
		{ &Z_Construct_UFunction_UMidiSynthComponent_SetLoop, "SetLoop" }, // 2841085181
		{ &Z_Construct_UFunction_UMidiSynthComponent_SetPlaybackSpeed, "SetPlaybackSpeed" }, // 1523091349
		{ &Z_Construct_UFunction_UMidiSynthComponent_SetTranspose, "SetTranspose" }, // 1512055532
		{ &Z_Construct_UFunction_UMidiSynthComponent_StopMidi, "StopMidi" }, // 3562269371
		{ &Z_Construct_UFunction_UMidiSynthComponent_ToggleChannelMute, "ToggleChannelMute" }, // 305884235
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMidiSynthComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_MidiAsset = { "MidiAsset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, MidiAsset), Z_Construct_UClass_UMidiFileAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidiAsset_MetaData), NewProp_MidiAsset_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_MidiFilePath = { "MidiFilePath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, MidiFilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidiFilePath_MetaData), NewProp_MidiFilePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_SoundFontPath = { "SoundFontPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, SoundFontPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundFontPath_MetaData), NewProp_SoundFontPath_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_Gain = { "Gain", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, Gain), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gain_MetaData), NewProp_Gain_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_PlaybackSpeed = { "PlaybackSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, PlaybackSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlaybackSpeed_MetaData), NewProp_PlaybackSpeed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_Transpose = { "Transpose", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiSynthComponent, Transpose), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transpose_MetaData), NewProp_Transpose_MetaData) };
void Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bLoop_SetBit(void* Obj)
{
	((UMidiSynthComponent*)Obj)->bLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bLoop = { "bLoop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMidiSynthComponent), &Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bLoop_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLoop_MetaData), NewProp_bLoop_MetaData) };
void Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bAutoPlayOnBeginPlay_SetBit(void* Obj)
{
	((UMidiSynthComponent*)Obj)->bAutoPlayOnBeginPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bAutoPlayOnBeginPlay = { "bAutoPlayOnBeginPlay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMidiSynthComponent), &Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bAutoPlayOnBeginPlay_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoPlayOnBeginPlay_MetaData), NewProp_bAutoPlayOnBeginPlay_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMidiSynthComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_MidiAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_MidiFilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_SoundFontPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_Gain,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_PlaybackSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_Transpose,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bLoop,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiSynthComponent_Statics::NewProp_bAutoPlayOnBeginPlay,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiSynthComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMidiSynthComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USynthComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiSynthComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMidiSynthComponent_Statics::ClassParams = {
	&UMidiSynthComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UMidiSynthComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UMidiSynthComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiSynthComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UMidiSynthComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMidiSynthComponent()
{
	if (!Z_Registration_Info_UClass_UMidiSynthComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMidiSynthComponent.OuterSingleton, Z_Construct_UClass_UMidiSynthComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMidiSynthComponent.OuterSingleton;
}
template<> MIDICORE_API UClass* StaticClass<UMidiSynthComponent>()
{
	return UMidiSynthComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMidiSynthComponent);
// End Class UMidiSynthComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMidiSynthComponent, UMidiSynthComponent::StaticClass, TEXT("UMidiSynthComponent"), &Z_Registration_Info_UClass_UMidiSynthComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMidiSynthComponent), 2756063988U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_3266190824(TEXT("/Script/MidiCore"),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
