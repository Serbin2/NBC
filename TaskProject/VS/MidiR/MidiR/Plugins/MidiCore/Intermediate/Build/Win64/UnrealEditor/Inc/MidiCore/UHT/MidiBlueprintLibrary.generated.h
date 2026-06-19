// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MidiBlueprintLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UMidiFileAsset;
struct FMidiNoteSegment;
#ifdef MIDICORE_MidiBlueprintLibrary_generated_h
#error "MidiBlueprintLibrary.generated.h already included, missing '#pragma once' in MidiBlueprintLibrary.h"
#endif
#define MIDICORE_MidiBlueprintLibrary_generated_h

#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMidiNoteSegment_Statics; \
	MIDICORE_API static class UScriptStruct* StaticStruct();


template<> MIDICORE_API UScriptStruct* StaticStruct<struct FMidiNoteSegment>();

#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execLoadMidiNotesFromAsset); \
	DECLARE_FUNCTION(execLoadMidiNotes); \
	DECLARE_FUNCTION(execLoadMidiInfo);


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMidiBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UMidiBlueprintLibrary_Statics; \
public: \
	DECLARE_CLASS(UMidiBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MidiCore"), NO_API) \
	DECLARE_SERIALIZER(UMidiBlueprintLibrary)


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMidiBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMidiBlueprintLibrary(UMidiBlueprintLibrary&&); \
	UMidiBlueprintLibrary(const UMidiBlueprintLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMidiBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMidiBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMidiBlueprintLibrary) \
	NO_API virtual ~UMidiBlueprintLibrary();


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_25_PROLOG
#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_INCLASS_NO_PURE_DECLS \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MIDICORE_API UClass* StaticClass<class UMidiBlueprintLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiBlueprintLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
