// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MidiCore/Public/MidiFileAsset.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMidiFileAsset() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
MIDICORE_API UClass* Z_Construct_UClass_UMidiFileAsset();
MIDICORE_API UClass* Z_Construct_UClass_UMidiFileAsset_NoRegister();
UPackage* Z_Construct_UPackage__Script_MidiCore();
// End Cross Module References

// Begin Class UMidiFileAsset
void UMidiFileAsset::StaticRegisterNativesUMidiFileAsset()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMidiFileAsset);
UClass* Z_Construct_UClass_UMidiFileAsset_NoRegister()
{
	return UMidiFileAsset::StaticClass();
}
struct Z_Construct_UClass_UMidiFileAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n// \xed\x91\x9c\xec\xa4\x80 MIDI \xed\x8c\x8c\xec\x9d\xbc(.mid)\xec\x9d\x84 \xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc \xec\x97\x90\xec\x85\x8b\xec\x9c\xbc\xeb\xa1\x9c \xeb\x8b\xb4\xeb\x8a\x94 \xec\xbb\xa8\xed\x85\x8c\xec\x9d\xb4\xeb\x84\x88.\n//  - \xec\x9b\x90\xeb\xb3\xb8 \xeb\xb0\x94\xec\x9d\xb4\xed\x8a\xb8(RawData)\xeb\xa5\xbc \xea\xb7\xb8\xeb\x8c\x80\xeb\xa1\x9c \xeb\xb3\xb4\xea\xb4\x80 \xe2\x86\x92 \xeb\x9f\xb0\xed\x83\x80\xec\x9e\x84/\xec\xbf\xa0\xed\x82\xb9\xec\x97\x90\xec\x84\x9c \xed\x8c\x8c\xec\x84\x9c(CMidi)\xec\x97\x90 \xea\xb7\xb8\xeb\x8c\x80\xeb\xa1\x9c \xeb\x84\x98\xea\xb8\xb4\xeb\x8b\xa4.\n//  - \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\x8b\x9c \xed\x8a\xb8\xeb\x9e\x99/\xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8/\xeb\x85\xb8\xed\x8a\xb8 \xec\x88\x98\xec\x99\x80 \xea\xb8\xb8\xec\x9d\xb4\xeb\xa5\xbc \xea\xb3\x84\xec\x82\xb0\xed\x95\xb4 \xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90\xec\x97\x90 \xeb\xb3\xb4\xec\x97\xac \xec\xa4\x80\xeb\x8b\xa4.\n// \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x8a\x94 \xec\x97\x90\xeb\x94\x94\xed\x84\xb0 \xeb\xaa\xa8\xeb\x93\x88(UMidiFileFactory)\xec\x9d\xb4 \xeb\x8b\xb4\xeb\x8b\xb9\xed\x95\x9c\xeb\x8b\xa4.\n// \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n" },
#endif
		{ "IncludePath", "MidiFileAsset.h" },
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\n\xed\x91\x9c\xec\xa4\x80 MIDI \xed\x8c\x8c\xec\x9d\xbc(.mid)\xec\x9d\x84 \xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc \xec\x97\x90\xec\x85\x8b\xec\x9c\xbc\xeb\xa1\x9c \xeb\x8b\xb4\xeb\x8a\x94 \xec\xbb\xa8\xed\x85\x8c\xec\x9d\xb4\xeb\x84\x88.\n - \xec\x9b\x90\xeb\xb3\xb8 \xeb\xb0\x94\xec\x9d\xb4\xed\x8a\xb8(RawData)\xeb\xa5\xbc \xea\xb7\xb8\xeb\x8c\x80\xeb\xa1\x9c \xeb\xb3\xb4\xea\xb4\x80 \xe2\x86\x92 \xeb\x9f\xb0\xed\x83\x80\xec\x9e\x84/\xec\xbf\xa0\xed\x82\xb9\xec\x97\x90\xec\x84\x9c \xed\x8c\x8c\xec\x84\x9c(CMidi)\xec\x97\x90 \xea\xb7\xb8\xeb\x8c\x80\xeb\xa1\x9c \xeb\x84\x98\xea\xb8\xb4\xeb\x8b\xa4.\n - \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\x8b\x9c \xed\x8a\xb8\xeb\x9e\x99/\xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8/\xeb\x85\xb8\xed\x8a\xb8 \xec\x88\x98\xec\x99\x80 \xea\xb8\xb8\xec\x9d\xb4\xeb\xa5\xbc \xea\xb3\x84\xec\x82\xb0\xed\x95\xb4 \xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90\xec\x97\x90 \xeb\xb3\xb4\xec\x97\xac \xec\xa4\x80\xeb\x8b\xa4.\n\xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x8a\x94 \xec\x97\x90\xeb\x94\x94\xed\x84\xb0 \xeb\xaa\xa8\xeb\x93\x88(UMidiFileFactory)\xec\x9d\xb4 \xeb\x8b\xb4\xeb\x8b\xb9\xed\x95\x9c\xeb\x8b\xa4.\n\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RawData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// .mid \xec\x9b\x90\xeb\xb3\xb8 \xeb\xb0\x94\xec\x9d\xb4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", ".mid \xec\x9b\x90\xeb\xb3\xb8 \xeb\xb0\x94\xec\x9d\xb4\xed\x8a\xb8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Format_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe2\x94\x80\xe2\x94\x80 \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\x8b\x9c \xec\xb1\x84\xec\x9b\x8c\xec\xa7\x80\xeb\x8a\x94 \xed\x91\x9c\xec\x8b\x9c\xec\x9a\xa9 \xeb\xa9\x94\xed\x83\x80\xeb\x8d\xb0\xec\x9d\xb4\xed\x84\xb0 \xe2\x94\x80\xe2\x94\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe2\x94\x80\xe2\x94\x80 \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\x8b\x9c \xec\xb1\x84\xec\x9b\x8c\xec\xa7\x80\xeb\x8a\x94 \xed\x91\x9c\xec\x8b\x9c\xec\x9a\xa9 \xeb\xa9\x94\xed\x83\x80\xeb\x8d\xb0\xec\x9d\xb4\xed\x84\xb0 \xe2\x94\x80\xe2\x94\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TrackCount_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventCount_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoteCount_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DurationSeconds_MetaData[] = {
		{ "Category", "Midi" },
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceFilePath_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\xb6\x9c\xec\xb2\x98 \xea\xb2\xbd\xeb\xa1\x9c(\xec\xb0\xb8\xea\xb3\xa0\xec\x9a\xa9)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiFileAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8 \xec\xb6\x9c\xec\xb2\x98 \xea\xb2\xbd\xeb\xa1\x9c(\xec\xb0\xb8\xea\xb3\xa0\xec\x9a\xa9)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_RawData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RawData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Format;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TrackCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EventCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NoteCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DurationSeconds;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourceFilePath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMidiFileAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_RawData_Inner = { "RawData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_RawData = { "RawData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, RawData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RawData_MetaData), NewProp_RawData_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_Format = { "Format", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, Format), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Format_MetaData), NewProp_Format_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_TrackCount = { "TrackCount", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, TrackCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TrackCount_MetaData), NewProp_TrackCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_EventCount = { "EventCount", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, EventCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventCount_MetaData), NewProp_EventCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_NoteCount = { "NoteCount", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, NoteCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoteCount_MetaData), NewProp_NoteCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_DurationSeconds = { "DurationSeconds", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, DurationSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DurationSeconds_MetaData), NewProp_DurationSeconds_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_SourceFilePath = { "SourceFilePath", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMidiFileAsset, SourceFilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceFilePath_MetaData), NewProp_SourceFilePath_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMidiFileAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_RawData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_RawData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_Format,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_TrackCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_EventCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_NoteCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_DurationSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMidiFileAsset_Statics::NewProp_SourceFilePath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileAsset_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMidiFileAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMidiFileAsset_Statics::ClassParams = {
	&UMidiFileAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMidiFileAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UMidiFileAsset_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMidiFileAsset()
{
	if (!Z_Registration_Info_UClass_UMidiFileAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMidiFileAsset.OuterSingleton, Z_Construct_UClass_UMidiFileAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMidiFileAsset.OuterSingleton;
}
template<> MIDICORE_API UClass* StaticClass<UMidiFileAsset>()
{
	return UMidiFileAsset::StaticClass();
}
UMidiFileAsset::UMidiFileAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMidiFileAsset);
UMidiFileAsset::~UMidiFileAsset() {}
// End Class UMidiFileAsset

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiFileAsset_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMidiFileAsset, UMidiFileAsset::StaticClass, TEXT("UMidiFileAsset"), &Z_Registration_Info_UClass_UMidiFileAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMidiFileAsset), 3474167957U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiFileAsset_h_3446529322(TEXT("/Script/MidiCore"),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiFileAsset_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiFileAsset_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
