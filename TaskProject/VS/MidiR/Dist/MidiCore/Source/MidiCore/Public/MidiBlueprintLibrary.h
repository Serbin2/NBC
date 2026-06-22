#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MidiBlueprintLibrary.generated.h"

class UMidiFileAsset;

// 한 음(노트)을 블루프린트로 노출하는 구조체 — 피아노롤에서 사각형 하나에 해당.
// (내부 파서의 NoteSegment 를 언리얼 타입으로 변환한 것)
USTRUCT(BlueprintType)
struct FMidiNoteSegment
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Midi") int32 Channel = 0;     // 0~15
	UPROPERTY(BlueprintReadOnly, Category = "Midi") int32 Note = 0;        // 음높이 0~127
	UPROPERTY(BlueprintReadOnly, Category = "Midi") int32 Velocity = 0;    // 세기 0~127
	UPROPERTY(BlueprintReadOnly, Category = "Midi") float StartSeconds = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Midi") float EndSeconds = 0.f;
};

// 파서를 블루프린트에서 호출하기 위한 함수 라이브러리.
// (std 기반 파서 타입은 이 헤더에 노출하지 않고 .cpp 안에서만 다룬다)
UCLASS()
class MIDICORE_API UMidiBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// 미디/사운드폰트 리소스 경로 해석. 상대경로면
	//   ① 프로젝트 Content/<In>  →  ② 플러그인 동봉본 <Plugin>/Content/<PluginSubDir>/<파일명>
	// 순으로 존재하는 파일을 찾는다(사용자 프로젝트 오버라이드 우선, 없으면 플러그인 동봉본).
	// 절대경로는 그대로 반환. 어디서도 못 찾으면 프로젝트 Content 경로를 반환(로드 시 실패 로그).
	// PluginSubDir 예: "SoundFonts", "Midi".
	static FString ResolveMidiResourcePath(const FString& In, const FString& PluginSubDir);

	// .mid 파일을 파싱해 기본 정보를 돌려준다. 성공하면 true.
	// FilePath 가 상대 경로면 프로젝트 Content → 플러그인 동봉본 순으로 해석한다.
	UFUNCTION(BlueprintCallable, Category = "Midi", meta = (DisplayName = "Load MIDI Info"))
	static bool LoadMidiInfo(const FString& FilePath,
	                         int32& OutFormat, int32& OutTrackCount,
	                         int32& OutEventCount, int32& OutNoteCount,
	                         float& OutDurationSeconds);

	// .mid 파일을 파싱해 모든 노트 막대(피아노롤용)를 돌려준다. 성공하면 true.
	UFUNCTION(BlueprintCallable, Category = "Midi", meta = (DisplayName = "Load MIDI Notes"))
	static bool LoadMidiNotes(const FString& FilePath, TArray<FMidiNoteSegment>& OutNotes);

	// 임포트된 MIDI 에셋에서 노트 막대를 돌려준다. 성공하면 true.
	UFUNCTION(BlueprintCallable, Category = "Midi", meta = (DisplayName = "Load MIDI Notes (Asset)"))
	static bool LoadMidiNotesFromAsset(const UMidiFileAsset* Asset, TArray<FMidiNoteSegment>& OutNotes);
};
