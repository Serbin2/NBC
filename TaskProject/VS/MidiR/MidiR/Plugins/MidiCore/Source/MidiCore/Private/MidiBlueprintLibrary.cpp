#include "MidiBlueprintLibrary.h"
#include "MidiFileAsset.h"
#include "Midi.h"                 // 내부 파서(CMidi/NoteSegment) — std 기반, 이 .cpp 안에서만 사용
#include "Misc/FileHelper.h"      // FFileHelper::LoadFileToArray
#include "Misc/Paths.h"
#include <cstring>                // strcmp

// 상대 경로면 프로젝트 Content 디렉터리 기준으로 풀어 준다.
static FString ResolveMidiPath(const FString& In)
{
	return FPaths::IsRelative(In) ? FPaths::Combine(FPaths::ProjectContentDir(), In) : In;
}

// 바이트 버퍼를 파서에 넘긴다. 성공 시 true 와 함께 OutMidi 를 채운다.
// 헤더가 "MThd" 가 아니면 파싱 실패로 본다.
static bool ParseBytes(const uint8* Data, int32 Size, CMidi*& OutMidi)
{
	OutMidi = nullptr;
	if (!Data || Size <= 0)
		return false;

	// CMidi 는 복사 금지(이동 전용 멤버 보유)라 힙에 두고 포인터로 다룬다.
	OutMidi = new CMidi(Data, (size_t)Size);
	if (strcmp(OutMidi->GetHeader().GetName(), "MThd") != 0)
	{
		delete OutMidi;
		OutMidi = nullptr;
		return false;
	}
	return true;
}

// 파일을 바이트 버퍼로 읽어 파서에 넘긴다(언리얼식 입력 경로).
static bool LoadAndParse(const FString& FilePath, TArray<uint8>& OutBytes, CMidi*& OutMidi)
{
	if (!FFileHelper::LoadFileToArray(OutBytes, *ResolveMidiPath(FilePath)))
		return false;
	return ParseBytes(OutBytes.GetData(), OutBytes.Num(), OutMidi);
}

// CMidi → 노트 막대 배열(피아노롤용)로 변환하는 공용 헬퍼.
static void CollectNotes(const CMidi& Midi, TArray<FMidiNoteSegment>& OutNotes)
{
	for (const CTrack& Tr : Midi.GetTracks())
	{
		for (const NoteSegment& N : Tr.BuildNoteSegments())
		{
			FMidiNoteSegment Seg;
			Seg.Channel      = N.channel;
			Seg.Note         = N.note;
			Seg.Velocity     = N.velocity;
			Seg.StartSeconds = (float)(N.startMs / 1000.0);
			Seg.EndSeconds   = (float)(N.endMs / 1000.0);
			OutNotes.Add(Seg);
		}
	}
}

bool UMidiBlueprintLibrary::LoadMidiInfo(const FString& FilePath, int32& OutFormat,
	int32& OutTrackCount, int32& OutEventCount, int32& OutNoteCount, float& OutDurationSeconds)
{
	OutFormat = OutTrackCount = OutEventCount = OutNoteCount = 0;
	OutDurationSeconds = 0.f;

	TArray<uint8> Bytes;
	CMidi* Midi = nullptr;
	if (!LoadAndParse(FilePath, Bytes, Midi))
		return false;

	OutFormat     = Midi->GetHeader().GetFormat();
	OutTrackCount = Midi->GetHeader().GetNumberOfTracks();

	double DurationMs = 0.0;
	int32 Events = 0, Notes = 0;
	for (const CTrack& Tr : Midi->GetTracks())
	{
		Events += (int32)Tr.GetEvents().size();
		Notes  += (int32)Tr.BuildNoteSegments().size();
		for (const CEventRecord& Rec : Tr.GetEvents())
			if (Rec.absTimeMs > DurationMs) DurationMs = Rec.absTimeMs;
	}
	OutEventCount = Events;
	OutNoteCount  = Notes;
	OutDurationSeconds = (float)(DurationMs / 1000.0);

	delete Midi;
	return true;
}

bool UMidiBlueprintLibrary::LoadMidiNotes(const FString& FilePath, TArray<FMidiNoteSegment>& OutNotes)
{
	OutNotes.Reset();

	TArray<uint8> Bytes;
	CMidi* Midi = nullptr;
	if (!LoadAndParse(FilePath, Bytes, Midi))
		return false;

	CollectNotes(*Midi, OutNotes);

	delete Midi;
	return true;
}

bool UMidiBlueprintLibrary::LoadMidiNotesFromAsset(const UMidiFileAsset* Asset, TArray<FMidiNoteSegment>& OutNotes)
{
	OutNotes.Reset();
	if (!Asset || Asset->RawData.Num() == 0)
		return false;

	CMidi* Midi = nullptr;
	if (!ParseBytes(Asset->RawData.GetData(), Asset->RawData.Num(), Midi))
		return false;

	CollectNotes(*Midi, OutNotes);

	delete Midi;
	return true;
}
