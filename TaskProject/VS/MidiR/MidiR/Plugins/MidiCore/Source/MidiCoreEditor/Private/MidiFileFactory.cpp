#include "MidiFileFactory.h"
#include "MidiFileAsset.h"

UMidiFileFactory::UMidiFileFactory()
{
	bEditorImport = true;
	bCreateNew    = false;
	SupportedClass = UMidiFileAsset::StaticClass();
	Formats.Add(TEXT("mid;Standard MIDI File"));
	Formats.Add(TEXT("midi;Standard MIDI File"));
}

UObject* UMidiFileFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
	UMidiFileAsset* Asset = NewObject<UMidiFileAsset>(InParent, InClass, InName, Flags);

	const int32 Size = (int32)(BufferEnd - Buffer);
	Asset->RawData.Reset(Size);
	Asset->RawData.Append(Buffer, Size);
	Asset->SourceFilePath = GetCurrentFilename();
	Asset->RefreshInfo();   // 트랙/노트/길이 메타데이터 계산

	return Asset;
}
