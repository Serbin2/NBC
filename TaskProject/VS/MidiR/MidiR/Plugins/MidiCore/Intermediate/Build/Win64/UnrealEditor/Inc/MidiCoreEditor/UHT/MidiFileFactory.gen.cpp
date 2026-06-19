// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MidiCoreEditor/Private/MidiFileFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMidiFileFactory() {}

// Begin Cross Module References
MIDICOREEDITOR_API UClass* Z_Construct_UClass_UMidiFileFactory();
MIDICOREEDITOR_API UClass* Z_Construct_UClass_UMidiFileFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UFactory();
UPackage* Z_Construct_UPackage__Script_MidiCoreEditor();
// End Cross Module References

// Begin Class UMidiFileFactory
void UMidiFileFactory::StaticRegisterNativesUMidiFileFactory()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMidiFileFactory);
UClass* Z_Construct_UClass_UMidiFileFactory_NoRegister()
{
	return UMidiFileFactory::StaticClass();
}
struct Z_Construct_UClass_UMidiFileFactory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// .mid / .midi \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 UMidiFileAsset \xeb\xa1\x9c \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xed\x95\x98\xeb\x8a\x94 \xed\x8c\xa9\xed\x86\xa0\xeb\xa6\xac(\xeb\x93\x9c\xeb\x9e\x98\xea\xb7\xb8&\xeb\x93\x9c\xeb\xa1\xad \xec\xa7\x80\xec\x9b\x90).\n" },
#endif
		{ "IncludePath", "MidiFileFactory.h" },
		{ "ModuleRelativePath", "Private/MidiFileFactory.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", ".mid / .midi \xed\x8c\x8c\xec\x9d\xbc\xec\x9d\x84 UMidiFileAsset \xeb\xa1\x9c \xec\x9e\x84\xed\x8f\xac\xed\x8a\xb8\xed\x95\x98\xeb\x8a\x94 \xed\x8c\xa9\xed\x86\xa0\xeb\xa6\xac(\xeb\x93\x9c\xeb\x9e\x98\xea\xb7\xb8&\xeb\x93\x9c\xeb\xa1\xad \xec\xa7\x80\xec\x9b\x90)." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMidiFileFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMidiFileFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_MidiCoreEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileFactory_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMidiFileFactory_Statics::ClassParams = {
	&UMidiFileFactory::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMidiFileFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_UMidiFileFactory_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMidiFileFactory()
{
	if (!Z_Registration_Info_UClass_UMidiFileFactory.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMidiFileFactory.OuterSingleton, Z_Construct_UClass_UMidiFileFactory_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMidiFileFactory.OuterSingleton;
}
template<> MIDICOREEDITOR_API UClass* StaticClass<UMidiFileFactory>()
{
	return UMidiFileFactory::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMidiFileFactory);
UMidiFileFactory::~UMidiFileFactory() {}
// End Class UMidiFileFactory

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCoreEditor_Private_MidiFileFactory_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMidiFileFactory, UMidiFileFactory::StaticClass, TEXT("UMidiFileFactory"), &Z_Registration_Info_UClass_UMidiFileFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMidiFileFactory), 484799836U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCoreEditor_Private_MidiFileFactory_h_1971371976(TEXT("/Script/MidiCoreEditor"),
	Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCoreEditor_Private_MidiFileFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_njh10_Documents_NBC_TaskProject_VS_MidiR_MidiR_Plugins_MidiCore_Source_MidiCoreEditor_Private_MidiFileFactory_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
