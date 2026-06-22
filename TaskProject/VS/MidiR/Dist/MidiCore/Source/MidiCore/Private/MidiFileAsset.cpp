#include "MidiFileAsset.h"
#include "Midi.h"        // 내부 파서(CMidi) — std 기반, 이 .cpp 안에서만 사용
#include <cstring>       // strcmp

void UMidiFileAsset::RefreshInfo()
{
	Format = TrackCount = EventCount = NoteCount = 0;
	DurationSeconds = 0.f;

	if (RawData.Num() == 0)
	{
		return;
	}

	CMidi Midi(RawData.GetData(), (size_t)RawData.Num());
	if (strcmp(Midi.GetHeader().GetName(), "MThd") != 0)
	{
		return;   // 형식 오류 → 메타데이터는 0
	}

	Format     = Midi.GetHeader().GetFormat();
	TrackCount = Midi.GetHeader().GetNumberOfTracks();

	double DurationMs = 0.0;
	for (const CTrack& Tr : Midi.GetTracks())
	{
		EventCount += (int32)Tr.GetEvents().size();
		NoteCount  += (int32)Tr.BuildNoteSegments().size();
		for (const CEventRecord& Rec : Tr.GetEvents())
			if (Rec.absTimeMs > DurationMs) DurationMs = Rec.absTimeMs;
	}
	DurationSeconds = (float)(DurationMs / 1000.0);
}
