// MidiPrac.cpp : 콘솔 진입점.
// 지정한 MIDI 파일을 파싱(CMidi)한 뒤 winmm으로 실시간 재생(MidiPlayer)한다.

#include "MidiPlayer.h"
#include <string>

int main()
{
    // 재생할 MIDI 파일 경로 (실행 파일의 작업 디렉터리 기준 상대 경로)
    //std::string path = "./goit.mid";
    std::string path = "./take5.mid";

    MidiPlayer player(path);   // 생성자에서 파일 헤더·트랙·이벤트를 모두 파싱한다
    player.Play();             // 파싱된 이벤트를 절대시각 순서대로 MIDI 장치에 송출한다
    return 0;
}
