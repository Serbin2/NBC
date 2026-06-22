#pragma once
#include "CoreMinimal.h"
#include "MidiFileAsset.generated.h"

// ──────────────────────────────────────────────────────────────
// 표준 MIDI 파일(.mid)을 언리얼 에셋으로 담는 컨테이너.
//  - 원본 바이트(RawData)를 그대로 보관 → 런타임/쿠킹에서 파서(CMidi)에 그대로 넘긴다.
//  - 임포트 시 트랙/이벤트/노트 수와 길이를 계산해 디테일 패널에 보여 준다.
// 임포트는 에디터 모듈(UMidiFileFactory)이 담당한다.
// ──────────────────────────────────────────────────────────────
UCLASS(BlueprintType)
class MIDICORE_API UMidiFileAsset : public UObject
{
	GENERATED_BODY()

public:
	// .mid 원본 바이트
	UPROPERTY()
	TArray<uint8> RawData;

	// ── 임포트 시 채워지는 표시용 메타데이터 ──
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") int32 Format = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") int32 TrackCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") int32 EventCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") int32 NoteCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") float DurationSeconds = 0.f;

	// 임포트 출처 경로(참고용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Midi") FString SourceFilePath;

	// RawData 를 파싱해 위 메타데이터를 다시 계산한다. (임포트 직후 호출)
	void RefreshInfo();
};
