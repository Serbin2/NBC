#pragma once
#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MidiFileFactory.generated.h"

// .mid / .midi 파일을 UMidiFileAsset 로 임포트하는 팩토리(드래그&드롭 지원).
UCLASS()
class UMidiFileFactory : public UFactory
{
	GENERATED_BODY()

public:
	UMidiFileFactory();

	virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
		UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd,
		FFeedbackContext* Warn) override;
};
