// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MidiCore/Public/MidiBlueprintLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMidiBlueprintLibrary() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
MIDICORE_API UClass* Z_Construct_UClass_UMidiBlueprintLibrary();
MIDICORE_API UClass* Z_Construct_UClass_UMidiBlueprintLibrary_NoRegister();
MIDICORE_API UClass* Z_Construct_UClass_UMidiFileAsset_NoRegister();
MIDICORE_API UScriptStruct* Z_Construct_UScriptStruct_FMidiNoteSegment();
UPackage* Z_Construct_UPackage__Script_MidiCore();
// End Cross Module References

// Begin ScriptStruct FMidiNoteSegment
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MidiNoteSegment;
class UScriptStruct* FMidiNoteSegment::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MidiNoteSegment.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MidiNoteSegment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMidiNoteSegment, (UObject*)Z_Construct_UPackage__Script_MidiCore(), TEXT("MidiNoteSegment"));
	}
	return Z_Registration_Info_UScriptStruct_MidiNoteSegment.OuterSingleton;
}
template<> MIDICORE_API UScriptStruct* StaticStruct<FMidiNoteSegment>()
{
	return FMidiNoteSegment::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMidiNoteSegment_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x95\x9c \xec\x9d\x8c(\xeb\x85\xb8\xed\x8a\xb8)\xec\x9d\x84 \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xeb\xa1\x9c \xeb\x85\xb8\xec\xb6\x9c\xed\x95\x98\xeb\x8a\x94 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4 \xe2\x80\x94 \xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4\xec\x97\x90\xec\x84\x9c \xec\x82\xac\xea\xb0\x81\xed\x98\x95 \xed\x95\x98\xeb\x82\x98\xec\x97\x90 \xed\x95\xb4\xeb\x8b\xb9.\n// (\xeb\x82\xb4\xeb\xb6\x80 \xed\x8c\x8c\xec\x84\x9c\xec\x9d\x98 NoteSegment \xeb\xa5\xbc \xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc \xed\x83\x80\xec\x9e\x85\xec\x9c\xbc\xeb\xa1\x9c \xeb\xb3\x80\xed\x99\x98\xed\x95\x9c \xea\xb2\x83)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x95\x9c \xec\x9d\x8c(\xeb\x85\xb8\xed\x8a\xb8)\xec\x9d\x84 \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xeb\xa1\x9c \xeb\x85\xb8\xec\xb6\x9c\xed\x95\x98\xeb\x8a\x94 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4 \xe2\x80\x94 \xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4\xec\x97\x90\xec\x84\x9c \xec\x82\xac\xea\xb0\x81\xed\x98\x95 \xed\x95\x98\xeb\x82\x98\xec\x97\x90 \xed\x95\xb4\xeb\x8b\xb9.\n(\xeb\x82\xb4\xeb\xb6\x80 \xed\x8c\x8c\xec\x84\x9c\xec\x9d\x98 NoteSegment \xeb\xa5\xbc \xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc \xed\x83\x80\xec\x9e\x85\xec\x9c\xbc\xeb\xa1\x9c \xeb\xb3\x80\xed\x99\x98\xed\x95\x9c \xea\xb2\x83)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Channel_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Note_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 0~15\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0~15" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4 0~127\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4 0~127" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartSeconds_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\xb8\xea\xb8\xb0 0~127\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\xb8\xea\xb8\xb0 0~127" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EndSeconds_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Channel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Note;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StartSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EndSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMidiNoteSegment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Channel = { "Channel", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMidiNoteSegment, Channel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Channel_MetaData), NewProp_Channel_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Note = { "Note", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMidiNoteSegment, Note), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Note_MetaData), NewProp_Note_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMidiNoteSegment, Velocity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_StartSeconds = { "StartSeconds", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMidiNoteSegment, StartSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartSeconds_MetaData), NewProp_StartSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_EndSeconds = { "EndSeconds", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMidiNoteSegment, EndSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EndSeconds_MetaData), NewProp_EndSeconds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Channel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Note,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_StartSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewProp_EndSeconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCore,
	nullptr,
	&NewStructOps,
	"MidiNoteSegment",
	Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::PropPointers),
	sizeof(FMidiNoteSegment),
	alignof(FMidiNoteSegment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMidiNoteSegment()
{
	if (!Z_Registration_Info_UScriptStruct_MidiNoteSegment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MidiNoteSegment.InnerSingleton, Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MidiNoteSegment.InnerSingleton;
}
// End ScriptStruct FMidiNoteSegment

// Begin Class UMidiBlueprintLibrary Function LoadMidiInfo
struct Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics
{
	struct MidiBlueprintLibrary_eventLoadMidiInfo_Parms
	{
		FString FilePath;
		int32 OutFormat;
		int32 OutTrackCount;
		int32 OutEventCount;
		int32 OutNoteCount;
		float OutDurationSeconds;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// .mid \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xea\xb8\xb0\xeb\xb3\xb8 \xec\xa0\x95\xeb\xb3\xb4\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true.\n// FilePath \xea\xb0\x80 \xec\x83\x81\xeb\x8c\x80 \xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xe2\x86\x92 \xed\x94\x8c\xeb\x9f\xac\xea\xb7\xb8\xec\x9d\xb8 \xeb\x8f\x99\xeb\xb4\x89\xeb\xb3\xb8 \xec\x88\x9c\xec\x9c\xbc\xeb\xa1\x9c \xed\x95\xb4\xec\x84\x9d\xed\x95\x9c\xeb\x8b\xa4.\n" },
#endif
		{ "DisplayName", "Load MIDI Info" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", ".mid \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xea\xb8\xb0\xeb\xb3\xb8 \xec\xa0\x95\xeb\xb3\xb4\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true.\nFilePath \xea\xb0\x80 \xec\x83\x81\xeb\x8c\x80 \xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xe2\x86\x92 \xed\x94\x8c\xeb\x9f\xac\xea\xb7\xb8\xec\x9d\xb8 \xeb\x8f\x99\xeb\xb4\x89\xeb\xb3\xb8 \xec\x88\x9c\xec\x9c\xbc\xeb\xa1\x9c \xed\x95\xb4\xec\x84\x9d\xed\x95\x9c\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FilePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FilePath;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutFormat;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutTrackCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutEventCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OutNoteCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutDurationSeconds;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, FilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FilePath_MetaData), NewProp_FilePath_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutFormat = { "OutFormat", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, OutFormat), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutTrackCount = { "OutTrackCount", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, OutTrackCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutEventCount = { "OutEventCount", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, OutEventCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutNoteCount = { "OutNoteCount", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, OutNoteCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutDurationSeconds = { "OutDurationSeconds", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiInfo_Parms, OutDurationSeconds), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MidiBlueprintLibrary_eventLoadMidiInfo_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiBlueprintLibrary_eventLoadMidiInfo_Parms), &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_FilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutFormat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutTrackCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutEventCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutNoteCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_OutDurationSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiBlueprintLibrary, nullptr, "LoadMidiInfo", nullptr, nullptr, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::MidiBlueprintLibrary_eventLoadMidiInfo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::MidiBlueprintLibrary_eventLoadMidiInfo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiBlueprintLibrary::execLoadMidiInfo)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_FilePath);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutFormat);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutTrackCount);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutEventCount);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_OutNoteCount);
	P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_OutDurationSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UMidiBlueprintLibrary::LoadMidiInfo(Z_Param_FilePath,Z_Param_Out_OutFormat,Z_Param_Out_OutTrackCount,Z_Param_Out_OutEventCount,Z_Param_Out_OutNoteCount,Z_Param_Out_OutDurationSeconds);
	P_NATIVE_END;
}
// End Class UMidiBlueprintLibrary Function LoadMidiInfo

// Begin Class UMidiBlueprintLibrary Function LoadMidiNotes
struct Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics
{
	struct MidiBlueprintLibrary_eventLoadMidiNotes_Parms
	{
		FString FilePath;
		TArray<FMidiNoteSegment> OutNotes;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// .mid \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xeb\xaa\xa8\xeb\x93\xa0 \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80(\xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4\xec\x9a\xa9)\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true.\n" },
#endif
		{ "DisplayName", "Load MIDI Notes" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", ".mid \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xeb\xaa\xa8\xeb\x93\xa0 \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80(\xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4\xec\x9a\xa9)\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FilePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FilePath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutNotes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutNotes;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiNotes_Parms, FilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FilePath_MetaData), NewProp_FilePath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_OutNotes_Inner = { "OutNotes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMidiNoteSegment, METADATA_PARAMS(0, nullptr) }; // 1367535565
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_OutNotes = { "OutNotes", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiNotes_Parms, OutNotes), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1367535565
void Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MidiBlueprintLibrary_eventLoadMidiNotes_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiBlueprintLibrary_eventLoadMidiNotes_Parms), &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_FilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_OutNotes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_OutNotes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiBlueprintLibrary, nullptr, "LoadMidiNotes", nullptr, nullptr, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::MidiBlueprintLibrary_eventLoadMidiNotes_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::MidiBlueprintLibrary_eventLoadMidiNotes_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiBlueprintLibrary::execLoadMidiNotes)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_FilePath);
	P_GET_TARRAY_REF(FMidiNoteSegment,Z_Param_Out_OutNotes);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UMidiBlueprintLibrary::LoadMidiNotes(Z_Param_FilePath,Z_Param_Out_OutNotes);
	P_NATIVE_END;
}
// End Class UMidiBlueprintLibrary Function LoadMidiNotes

// Begin Class UMidiBlueprintLibrary Function LoadMidiNotesFromAsset
struct Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics
{
	struct MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms
	{
		const UMidiFileAsset* Asset;
		TArray<FMidiNoteSegment> OutNotes;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b\xec\x97\x90\xec\x84\x9c \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true.\n" },
#endif
		{ "DisplayName", "Load MIDI Notes (Asset)" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b\xec\x97\x90\xec\x84\x9c \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80\xeb\xa5\xbc \xeb\x8f\x8c\xeb\xa0\xa4\xec\xa4\x80\xeb\x8b\xa4. \xec\x84\xb1\xea\xb3\xb5\xed\x95\x98\xeb\xa9\xb4 true." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Asset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Asset;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutNotes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutNotes;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_Asset = { "Asset", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms, Asset), Z_Construct_UClass_UMidiFileAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Asset_MetaData), NewProp_Asset_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_OutNotes_Inner = { "OutNotes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMidiNoteSegment, METADATA_PARAMS(0, nullptr) }; // 1367535565
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_OutNotes = { "OutNotes", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms, OutNotes), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1367535565
void Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms), &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_Asset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_OutNotes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_OutNotes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMidiBlueprintLibrary, nullptr, "LoadMidiNotesFromAsset", nullptr, nullptr, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::MidiBlueprintLibrary_eventLoadMidiNotesFromAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMidiBlueprintLibrary::execLoadMidiNotesFromAsset)
{
	P_GET_OBJECT(UMidiFileAsset,Z_Param_Asset);
	P_GET_TARRAY_REF(FMidiNoteSegment,Z_Param_Out_OutNotes);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UMidiBlueprintLibrary::LoadMidiNotesFromAsset(Z_Param_Asset,Z_Param_Out_OutNotes);
	P_NATIVE_END;
}
// End Class UMidiBlueprintLibrary Function LoadMidiNotesFromAsset

// Begin Class UMidiBlueprintLibrary
void UMidiBlueprintLibrary::StaticRegisterNativesUMidiBlueprintLibrary()
{
	UClass* Class = UMidiBlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "LoadMidiInfo", &UMidiBlueprintLibrary::execLoadMidiInfo },
		{ "LoadMidiNotes", &UMidiBlueprintLibrary::execLoadMidiNotes },
		{ "LoadMidiNotesFromAsset", &UMidiBlueprintLibrary::execLoadMidiNotesFromAsset },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMidiBlueprintLibrary);
UClass* Z_Construct_UClass_UMidiBlueprintLibrary_NoRegister()
{
	return UMidiBlueprintLibrary::StaticClass();
}
struct Z_Construct_UClass_UMidiBlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x8c\x8c\xec\x84\x9c\xeb\xa5\xbc \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xec\x97\x90\xec\x84\x9c \xed\x98\xb8\xec\xb6\x9c\xed\x95\x98\xea\xb8\xb0 \xec\x9c\x84\xed\x95\x9c \xed\x95\xa8\xec\x88\x98 \xeb\x9d\xbc\xec\x9d\xb4\xeb\xb8\x8c\xeb\x9f\xac\xeb\xa6\xac.\n// (std \xea\xb8\xb0\xeb\xb0\x98 \xed\x8c\x8c\xec\x84\x9c \xed\x83\x80\xec\x9e\x85\xec\x9d\x80 \xec\x9d\xb4 \xed\x97\xa4\xeb\x8d\x94\xec\x97\x90 \xeb\x85\xb8\xec\xb6\x9c\xed\x95\x98\xec\xa7\x80 \xec\x95\x8a\xea\xb3\xa0 .cpp \xec\x95\x88\xec\x97\x90\xec\x84\x9c\xeb\xa7\x8c \xeb\x8b\xa4\xeb\xa3\xac\xeb\x8b\xa4)\n" },
#endif
		{ "IncludePath", "MidiBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/MidiBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x8c\x8c\xec\x84\x9c\xeb\xa5\xbc \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xec\x97\x90\xec\x84\x9c \xed\x98\xb8\xec\xb6\x9c\xed\x95\x98\xea\xb8\xb0 \xec\x9c\x84\xed\x95\x9c \xed\x95\xa8\xec\x88\x98 \xeb\x9d\xbc\xec\x9d\xb4\xeb\xb8\x8c\xeb\x9f\xac\xeb\xa6\xac.\n(std \xea\xb8\xb0\xeb\xb0\x98 \xed\x8c\x8c\xec\x84\x9c \xed\x83\x80\xec\x9e\x85\xec\x9d\x80 \xec\x9d\xb4 \xed\x97\xa4\xeb\x8d\x94\xec\x97\x90 \xeb\x85\xb8\xec\xb6\x9c\xed\x95\x98\xec\xa7\x80 \xec\x95\x8a\xea\xb3\xa0 .cpp \xec\x95\x88\xec\x97\x90\xec\x84\x9c\xeb\xa7\x8c \xeb\x8b\xa4\xeb\xa3\xac\xeb\x8b\xa4)" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiInfo, "LoadMidiInfo" }, // 2997195263
		{ &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotes, "LoadMidiNotes" }, // 4211147711
		{ &Z_Construct_UFunction_UMidiBlueprintLibrary_LoadMidiNotesFromAsset, "LoadMidiNotesFromAsset" }, // 2998824453
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMidiBlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMidiBlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiBlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMidiBlueprintLibrary_Statics::ClassParams = {
	&UMidiBlueprintLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiBlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UMidiBlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMidiBlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UMidiBlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMidiBlueprintLibrary.OuterSingleton, Z_Construct_UClass_UMidiBlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMidiBlueprintLibrary.OuterSingleton;
}
template<> MIDICORE_API UClass* StaticClass<UMidiBlueprintLibrary>()
{
	return UMidiBlueprintLibrary::StaticClass();
}
UMidiBlueprintLibrary::UMidiBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMidiBlueprintLibrary);
UMidiBlueprintLibrary::~UMidiBlueprintLibrary() {}
// End Class UMidiBlueprintLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMidiNoteSegment::StaticStruct, Z_Construct_UScriptStruct_FMidiNoteSegment_Statics::NewStructOps, TEXT("MidiNoteSegment"), &Z_Registration_Info_UScriptStruct_MidiNoteSegment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMidiNoteSegment), 1367535565U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMidiBlueprintLibrary, UMidiBlueprintLibrary::StaticClass, TEXT("UMidiBlueprintLibrary"), &Z_Registration_Info_UClass_UMidiBlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMidiBlueprintLibrary), 2148139381U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_1178200166(TEXT("/Script/MidiCore"),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
