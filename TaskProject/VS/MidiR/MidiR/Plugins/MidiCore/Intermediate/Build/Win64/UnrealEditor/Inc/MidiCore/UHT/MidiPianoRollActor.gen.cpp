// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MidiCore/Public/MidiPianoRollActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMidiPianoRollActor() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
MIDICORE_API UClass* Z_Construct_UClass_AMidiPianoRollActor();
MIDICORE_API UClass* Z_Construct_UClass_AMidiPianoRollActor_NoRegister();
MIDICORE_API UClass* Z_Construct_UClass_UMidiFileAsset_NoRegister();
MIDICORE_API UClass* Z_Construct_UClass_UMidiSynthComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_MidiCore();
// End Cross Module References

// Begin Class AMidiPianoRollActor Function Rebuild
struct Z_Construct_UFunction_AMidiPianoRollActor_Rebuild_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90 \xeb\xb2\x84\xed\x8a\xbc / \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xec\x97\x90\xec\x84\x9c \xeb\x8b\xa4\xec\x8b\x9c \xea\xb7\xb8\xeb\xa6\xac\xea\xb8\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x94\x94\xed\x85\x8c\xec\x9d\xbc \xed\x8c\xa8\xeb\x84\x90 \xeb\xb2\x84\xed\x8a\xbc / \xeb\xb8\x94\xeb\xa3\xa8\xed\x94\x84\xeb\xa6\xb0\xed\x8a\xb8\xec\x97\x90\xec\x84\x9c \xeb\x8b\xa4\xec\x8b\x9c \xea\xb7\xb8\xeb\xa6\xac\xea\xb8\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMidiPianoRollActor_Rebuild_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMidiPianoRollActor, nullptr, "Rebuild", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMidiPianoRollActor_Rebuild_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMidiPianoRollActor_Rebuild_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMidiPianoRollActor_Rebuild()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMidiPianoRollActor_Rebuild_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMidiPianoRollActor::execRebuild)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Rebuild();
	P_NATIVE_END;
}
// End Class AMidiPianoRollActor Function Rebuild

// Begin Class AMidiPianoRollActor
void AMidiPianoRollActor::StaticRegisterNativesAMidiPianoRollActor()
{
	UClass* Class = AMidiPianoRollActor::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Rebuild", &AMidiPianoRollActor::execRebuild },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMidiPianoRollActor);
UClass* Z_Construct_UClass_AMidiPianoRollActor_NoRegister()
{
	return AMidiPianoRollActor::StaticClass();
}
struct Z_Construct_UClass_AMidiPianoRollActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xaf\xb8\xeb\x94\x94 \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xeb\x85\xb8\xed\x8a\xb8\xeb\xa5\xbc 3D \xeb\xa7\x89\xeb\x8c\x80\xeb\xa1\x9c \xeb\xb0\xb0\xec\xb9\x98\xed\x95\x98\xeb\x8a\x94 \xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4 \xec\x95\xa1\xed\x84\xb0.\n//  - X\xec\xb6\x95 = \xec\x8b\x9c\xea\xb0\x84(\xeb\xa7\x89\xeb\x8c\x80 \xec\x9c\x84\xec\xb9\x98=\xec\x8b\x9c\xec\x9e\x91\xec\xb4\x88, \xea\xb8\xb8\xec\x9d\xb4=\xec\xa7\x80\xec\x86\x8d\xec\x8b\x9c\xea\xb0\x84), Z\xec\xb6\x95 = \xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4(0~127), \xec\x83\x89 = \xec\xb1\x84\xeb\x84\x90\n//  - \xeb\x85\xb8\xed\x8a\xb8\xeb\x8a\x94 \xec\xb1\x84\xeb\x84\x90\xeb\xb3\x84 UInstancedStaticMeshComponent \xec\x97\x90 \xec\x9d\xb8\xec\x8a\xa4\xed\x84\xb4\xec\x8a\xa4\xeb\xa1\x9c \xec\xb6\x94\xea\xb0\x80(\xeb\x8c\x80\xeb\x9f\x89\xeb\x8f\x84 \xea\xb0\x80\xeb\xb3\x8d\xea\xb2\x8c)\n//  - \xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c(\xec\x84\xb8\xeb\xa1\x9c \xeb\xa7\x89\xeb\x8c\x80)\xea\xb0\x80 Play \xec\xa4\x91 \xec\x8b\x9c\xea\xb0\x84\xec\xb6\x95\xec\x9d\x84 \xeb\x94\xb0\xeb\x9d\xbc \xec\x9d\xb4\xeb\x8f\x99\n// \xeb\xa0\x88\xeb\xb2\xa8\xec\x97\x90 \xeb\x81\x8c\xec\x96\xb4\xeb\x8b\xa4 \xeb\x86\x93\xec\x9c\xbc\xeb\xa9\xb4 OnConstruction \xec\x97\x90\xec\x84\x9c \xec\xa6\x89\xec\x8b\x9c \xec\x83\x9d\xec\x84\xb1\xeb\x90\x9c\xeb\x8b\xa4.\n" },
#endif
		{ "IncludePath", "MidiPianoRollActor.h" },
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xaf\xb8\xeb\x94\x94 \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 \xed\x8c\x8c\xec\x8b\xb1\xed\x95\xb4 \xeb\x85\xb8\xed\x8a\xb8\xeb\xa5\xbc 3D \xeb\xa7\x89\xeb\x8c\x80\xeb\xa1\x9c \xeb\xb0\xb0\xec\xb9\x98\xed\x95\x98\xeb\x8a\x94 \xed\x94\xbc\xec\x95\x84\xeb\x85\xb8\xeb\xa1\xa4 \xec\x95\xa1\xed\x84\xb0.\n - X\xec\xb6\x95 = \xec\x8b\x9c\xea\xb0\x84(\xeb\xa7\x89\xeb\x8c\x80 \xec\x9c\x84\xec\xb9\x98=\xec\x8b\x9c\xec\x9e\x91\xec\xb4\x88, \xea\xb8\xb8\xec\x9d\xb4=\xec\xa7\x80\xec\x86\x8d\xec\x8b\x9c\xea\xb0\x84), Z\xec\xb6\x95 = \xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4(0~127), \xec\x83\x89 = \xec\xb1\x84\xeb\x84\x90\n - \xeb\x85\xb8\xed\x8a\xb8\xeb\x8a\x94 \xec\xb1\x84\xeb\x84\x90\xeb\xb3\x84 UInstancedStaticMeshComponent \xec\x97\x90 \xec\x9d\xb8\xec\x8a\xa4\xed\x84\xb4\xec\x8a\xa4\xeb\xa1\x9c \xec\xb6\x94\xea\xb0\x80(\xeb\x8c\x80\xeb\x9f\x89\xeb\x8f\x84 \xea\xb0\x80\xeb\xb3\x8d\xea\xb2\x8c)\n - \xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c(\xec\x84\xb8\xeb\xa1\x9c \xeb\xa7\x89\xeb\x8c\x80)\xea\xb0\x80 Play \xec\xa4\x91 \xec\x8b\x9c\xea\xb0\x84\xec\xb6\x95\xec\x9d\x84 \xeb\x94\xb0\xeb\x9d\xbc \xec\x9d\xb4\xeb\x8f\x99\n\xeb\xa0\x88\xeb\xb2\xa8\xec\x97\x90 \xeb\x81\x8c\xec\x96\xb4\xeb\x8b\xa4 \xeb\x86\x93\xec\x9c\xbc\xeb\xa9\xb4 OnConstruction \xec\x97\x90\xec\x84\x9c \xec\xa6\x89\xec\x8b\x9c \xec\x83\x9d\xec\x84\xb1\xeb\x90\x9c\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidiAsset_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b(\xec\xa7\x80\xec\xa0\x95\xeb\x90\x98\xeb\xa9\xb4 \xec\x95\x84\xeb\x9e\x98 MidiFilePath \xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9a\xb0\xec\x84\xa0)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xeb\x90\x9c MIDI \xec\x97\x90\xec\x85\x8b(\xec\xa7\x80\xec\xa0\x95\xeb\x90\x98\xeb\xa9\xb4 \xec\x95\x84\xeb\x9e\x98 MidiFilePath \xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9a\xb0\xec\x84\xa0)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidiFilePath_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x83\x9d\xed\x95\xa0 .mid \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80). MidiAsset \xec\x9d\xb4 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9.\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x83\x9d\xed\x95\xa0 .mid \xea\xb2\xbd\xeb\xa1\x9c (\xec\x83\x81\xeb\x8c\x80\xea\xb2\xbd\xeb\xa1\x9c\xeb\xa9\xb4 \xed\x94\x84\xeb\xa1\x9c\xec\xa0\x9d\xed\x8a\xb8 Content \xed\x8f\xb4\xeb\x8d\x94 \xea\xb8\xb0\xec\xa4\x80). MidiAsset \xec\x9d\xb4 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeScale_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x8b\x9c\xea\xb0\x84 1\xec\xb4\x88\xeb\x8b\xb9 \xec\x9b\x94\xeb\x93\x9c \xea\xb8\xb8\xec\x9d\xb4(uu) \xe2\x80\x94 \xea\xb0\x80\xeb\xa1\x9c(\xec\x8b\x9c\xea\xb0\x84) \xec\x8a\xa4\xec\xbc\x80\xec\x9d\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x8b\x9c\xea\xb0\x84 1\xec\xb4\x88\xeb\x8b\xb9 \xec\x9b\x94\xeb\x93\x9c \xea\xb8\xb8\xec\x9d\xb4(uu) \xe2\x80\x94 \xea\xb0\x80\xeb\xa1\x9c(\xec\x8b\x9c\xea\xb0\x84) \xec\x8a\xa4\xec\xbc\x80\xec\x9d\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PitchScale_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xb0\x98\xec\x9d\x8c 1\xeb\x8b\xb9 \xec\x9b\x94\xeb\x93\x9c \xeb\x86\x92\xec\x9d\xb4(uu) \xe2\x80\x94 \xec\x84\xb8\xeb\xa1\x9c(\xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4) \xec\x8a\xa4\xec\xbc\x80\xec\x9d\xbc\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xb0\x98\xec\x9d\x8c 1\xeb\x8b\xb9 \xec\x9b\x94\xeb\x93\x9c \xeb\x86\x92\xec\x9d\xb4(uu) \xe2\x80\x94 \xec\x84\xb8\xeb\xa1\x9c(\xec\x9d\x8c\xeb\x86\x92\xec\x9d\xb4) \xec\x8a\xa4\xec\xbc\x80\xec\x9d\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoteHeight_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80 \xeb\x91\x90\xea\xbb\x98(Z, uu)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80 \xeb\x91\x90\xea\xbb\x98(Z, uu)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoteDepth_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80 \xea\xb9\x8a\xec\x9d\xb4(Y, uu)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x85\xb8\xed\x8a\xb8 \xeb\xa7\x89\xeb\x8c\x80 \xea\xb9\x8a\xec\x9d\xb4(Y, uu)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAnimatePlayhead_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Play \xec\xa4\x91 \xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c\xeb\xa5\xbc \xec\x9e\x90\xeb\x8f\x99\xec\x9c\xbc\xeb\xa1\x9c \xec\x9d\xb4\xeb\x8f\x99\xec\x8b\x9c\xed\x82\xa8\xeb\x8b\xa4\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Play \xec\xa4\x91 \xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c\xeb\xa5\xbc \xec\x9e\x90\xeb\x8f\x99\xec\x9c\xbc\xeb\xa1\x9c \xec\x9d\xb4\xeb\x8f\x99\xec\x8b\x9c\xed\x82\xa8\xeb\x8b\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlaybackSpeed_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c \xeb\xb0\xb0\xec\x86\x8d (\xec\x95\x84\xeb\x9e\x98 \xeb\x8f\x99\xea\xb8\xb0\xed\x99\x94\xea\xb0\x80 \xea\xba\xbc\xec\xa0\xb8 \xec\x9e\x88\xea\xb1\xb0\xeb\x82\x98 \xec\x8b\xa0\xec\x8a\xa4 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xea\xb0\x80 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9)\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x83\x9d \xed\x97\xa4\xeb\x93\x9c \xeb\xb0\xb0\xec\x86\x8d (\xec\x95\x84\xeb\x9e\x98 \xeb\x8f\x99\xea\xb8\xb0\xed\x99\x94\xea\xb0\x80 \xea\xba\xbc\xec\xa0\xb8 \xec\x9e\x88\xea\xb1\xb0\xeb\x82\x98 \xec\x8b\xa0\xec\x8a\xa4 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xea\xb0\x80 \xec\x97\x86\xec\x9d\x84 \xeb\x95\x8c\xeb\xa7\x8c \xec\x82\xac\xec\x9a\xa9)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSyncToSynth_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xea\xb0\x99\xec\x9d\x80 \xec\x95\xa1\xed\x84\xb0\xec\x97\x90 \xeb\xb6\x99\xec\x9d\x80 Midi Synth Component \xec\x9d\x98 \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98\xec\x97\x90 \xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94\xeb\xa5\xbc \xeb\xa7\x9e\xec\xb6\x98\xeb\x8b\xa4(\xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xc2\xb7\xec\x8b\x9c\xea\xb0\x81 \xeb\x93\x9c\xeb\xa6\xac\xed\x94\x84\xed\x8a\xb8 \xec\xa0\x9c\xea\xb1\xb0).\n// \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xea\xb0\x80 \xec\x97\x86\xec\x9c\xbc\xeb\xa9\xb4 \xec\x9c\x84 PlaybackSpeed \xeb\xa1\x9c \xec\x9e\x90\xec\xb2\xb4 \xec\xa7\x84\xed\x96\x89(\xed\x8f\xb4\xeb\xb0\xb1)\xed\x95\x9c\xeb\x8b\xa4.\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xea\xb0\x99\xec\x9d\x80 \xec\x95\xa1\xed\x84\xb0\xec\x97\x90 \xeb\xb6\x99\xec\x9d\x80 Midi Synth Component \xec\x9d\x98 \xec\x9e\xac\xec\x83\x9d \xec\x9c\x84\xec\xb9\x98\xec\x97\x90 \xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94\xeb\xa5\xbc \xeb\xa7\x9e\xec\xb6\x98\xeb\x8b\xa4(\xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xc2\xb7\xec\x8b\x9c\xea\xb0\x81 \xeb\x93\x9c\xeb\xa6\xac\xed\x94\x84\xed\x8a\xb8 \xec\xa0\x9c\xea\xb1\xb0).\n\xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8\xea\xb0\x80 \xec\x97\x86\xec\x9c\xbc\xeb\xa9\xb4 \xec\x9c\x84 PlaybackSpeed \xeb\xa1\x9c \xec\x9e\x90\xec\xb2\xb4 \xec\xa7\x84\xed\x96\x89(\xed\x8f\xb4\xeb\xb0\xb1)\xed\x95\x9c\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlaybackOffsetSeconds_MetaData[] = {
		{ "Category", "Midi" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94 \xec\x8b\x9c\xea\xb0\x84 \xeb\xaf\xb8\xec\x84\xb8 \xeb\xb3\xb4\xec\xa0\x95(\xec\xb4\x88). \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94\xeb\xa5\xbc \xec\x95\x9e\xeb\x8b\xb9\xea\xb8\xb0\xeb\xa0\xa4\xeb\xa9\xb4 +, \xeb\x8a\xa6\xec\xb6\x94\xeb\xa0\xa4\xeb\xa9\xb4 -.\n" },
#endif
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94 \xec\x8b\x9c\xea\xb0\x84 \xeb\xaf\xb8\xec\x84\xb8 \xeb\xb3\xb4\xec\xa0\x95(\xec\xb4\x88). \xec\x98\xa4\xeb\x94\x94\xec\x98\xa4\xeb\xb3\xb4\xeb\x8b\xa4 \xec\x9e\xac\xec\x83\x9d\xeb\xb0\x94\xeb\xa5\xbc \xec\x95\x9e\xeb\x8b\xb9\xea\xb8\xb0\xeb\xa0\xa4\xeb\xa9\xb4 +, \xeb\x8a\xa6\xec\xb6\x94\xeb\xa0\xa4\xeb\xa9\xb4 -." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SceneRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChannelISMs_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Playhead_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xb1\x84\xeb\x84\x90\xeb\xb3\x84(16\xea\xb0\x9c)\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xb1\x84\xeb\x84\x90\xeb\xb3\x84(16\xea\xb0\x9c)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CubeMesh_MetaData[] = {
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BarMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SynthComp_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MidiPianoRollActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MidiAsset;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MidiFilePath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PitchScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoteHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoteDepth;
	static void NewProp_bAnimatePlayhead_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAnimatePlayhead;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaybackSpeed;
	static void NewProp_bSyncToSynth_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSyncToSynth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaybackOffsetSeconds;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChannelISMs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChannelISMs;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Playhead;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CubeMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BarMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SynthComp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMidiPianoRollActor_Rebuild, "Rebuild" }, // 4004532476
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMidiPianoRollActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_MidiAsset = { "MidiAsset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, MidiAsset), Z_Construct_UClass_UMidiFileAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidiAsset_MetaData), NewProp_MidiAsset_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_MidiFilePath = { "MidiFilePath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, MidiFilePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidiFilePath_MetaData), NewProp_MidiFilePath_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_TimeScale = { "TimeScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, TimeScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeScale_MetaData), NewProp_TimeScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PitchScale = { "PitchScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, PitchScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PitchScale_MetaData), NewProp_PitchScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_NoteHeight = { "NoteHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, NoteHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoteHeight_MetaData), NewProp_NoteHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_NoteDepth = { "NoteDepth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, NoteDepth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoteDepth_MetaData), NewProp_NoteDepth_MetaData) };
void Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bAnimatePlayhead_SetBit(void* Obj)
{
	((AMidiPianoRollActor*)Obj)->bAnimatePlayhead = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bAnimatePlayhead = { "bAnimatePlayhead", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMidiPianoRollActor), &Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bAnimatePlayhead_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAnimatePlayhead_MetaData), NewProp_bAnimatePlayhead_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PlaybackSpeed = { "PlaybackSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, PlaybackSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlaybackSpeed_MetaData), NewProp_PlaybackSpeed_MetaData) };
void Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bSyncToSynth_SetBit(void* Obj)
{
	((AMidiPianoRollActor*)Obj)->bSyncToSynth = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bSyncToSynth = { "bSyncToSynth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMidiPianoRollActor), &Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bSyncToSynth_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSyncToSynth_MetaData), NewProp_bSyncToSynth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PlaybackOffsetSeconds = { "PlaybackOffsetSeconds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, PlaybackOffsetSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlaybackOffsetSeconds_MetaData), NewProp_PlaybackOffsetSeconds_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_SceneRoot = { "SceneRoot", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, SceneRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SceneRoot_MetaData), NewProp_SceneRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_ChannelISMs_Inner = { "ChannelISMs", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_ChannelISMs = { "ChannelISMs", nullptr, (EPropertyFlags)0x0040008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, ChannelISMs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChannelISMs_MetaData), NewProp_ChannelISMs_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_Playhead = { "Playhead", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, Playhead), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Playhead_MetaData), NewProp_Playhead_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_CubeMesh = { "CubeMesh", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, CubeMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CubeMesh_MetaData), NewProp_CubeMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_BarMaterial = { "BarMaterial", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, BarMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BarMaterial_MetaData), NewProp_BarMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_SynthComp = { "SynthComp", nullptr, (EPropertyFlags)0x0040000000082008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMidiPianoRollActor, SynthComp), Z_Construct_UClass_UMidiSynthComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SynthComp_MetaData), NewProp_SynthComp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMidiPianoRollActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_MidiAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_MidiFilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_TimeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PitchScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_NoteHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_NoteDepth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bAnimatePlayhead,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PlaybackSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_bSyncToSynth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_PlaybackOffsetSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_SceneRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_ChannelISMs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_ChannelISMs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_Playhead,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_CubeMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_BarMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMidiPianoRollActor_Statics::NewProp_SynthComp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMidiPianoRollActor_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMidiPianoRollActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMidiPianoRollActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMidiPianoRollActor_Statics::ClassParams = {
	&AMidiPianoRollActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMidiPianoRollActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMidiPianoRollActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMidiPianoRollActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMidiPianoRollActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMidiPianoRollActor()
{
	if (!Z_Registration_Info_UClass_AMidiPianoRollActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMidiPianoRollActor.OuterSingleton, Z_Construct_UClass_AMidiPianoRollActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMidiPianoRollActor.OuterSingleton;
}
template<> MIDICORE_API UClass* StaticClass<AMidiPianoRollActor>()
{
	return AMidiPianoRollActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMidiPianoRollActor);
AMidiPianoRollActor::~AMidiPianoRollActor() {}
// End Class AMidiPianoRollActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiPianoRollActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMidiPianoRollActor, AMidiPianoRollActor::StaticClass, TEXT("AMidiPianoRollActor"), &Z_Registration_Info_UClass_AMidiPianoRollActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMidiPianoRollActor), 2758948178U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiPianoRollActor_h_3354030844(TEXT("/Script/MidiCore"),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiPianoRollActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiPianoRollActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
