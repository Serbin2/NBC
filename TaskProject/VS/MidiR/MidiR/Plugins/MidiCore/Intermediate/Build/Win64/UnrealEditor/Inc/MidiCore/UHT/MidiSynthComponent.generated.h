// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MidiSynthComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MIDICORE_MidiSynthComponent_generated_h
#error "MidiSynthComponent.generated.h already included, missing '#pragma once' in MidiSynthComponent.h"
#endif
#define MIDICORE_MidiSynthComponent_generated_h

#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsChannelMuted); \
	DECLARE_FUNCTION(execIsPlayingMidi); \
	DECLARE_FUNCTION(execGetDurationSeconds); \
	DECLARE_FUNCTION(execGetPlayPositionSeconds); \
	DECLARE_FUNCTION(execPreviewStop); \
	DECLARE_FUNCTION(execPreviewPlay); \
	DECLARE_FUNCTION(execToggleChannelMute); \
	DECLARE_FUNCTION(execSetChannelMute); \
	DECLARE_FUNCTION(execSetLoop); \
	DECLARE_FUNCTION(execSetTranspose); \
	DECLARE_FUNCTION(execSetGainLevel); \
	DECLARE_FUNCTION(execSetPlaybackSpeed); \
	DECLARE_FUNCTION(execSeekSeconds); \
	DECLARE_FUNCTION(execResumeMidi); \
	DECLARE_FUNCTION(execPauseMidi); \
	DECLARE_FUNCTION(execStopMidi); \
	DECLARE_FUNCTION(execPlayMidi);


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMidiSynthComponent(); \
	friend struct Z_Construct_UClass_UMidiSynthComponent_Statics; \
public: \
	DECLARE_CLASS(UMidiSynthComponent, USynthComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MidiCore"), NO_API) \
	DECLARE_SERIALIZER(UMidiSynthComponent)


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMidiSynthComponent(UMidiSynthComponent&&); \
	UMidiSynthComponent(const UMidiSynthComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMidiSynthComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMidiSynthComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMidiSynthComponent)


#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_21_PROLOG
#define FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_INCLASS_NO_PURE_DECLS \
	FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MIDICORE_API UClass* StaticClass<class UMidiSynthComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCore_Public_MidiSynthComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
