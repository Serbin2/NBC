#pragma once
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

// Content Browser 에서 UMidiFileAsset 의 표시/카테고리/색과 우클릭 액션(Play/Stop)을 제공.
class FAssetTypeActions_MidiFile : public FAssetTypeActions_Base
{
public:
	virtual FText   GetName() const override;
	virtual FColor  GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32  GetCategories() override;
	virtual void    GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section) override;
};
