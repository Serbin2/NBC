// Task02.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"
#include "Monster.h"

using namespace std;

// 메인 함수
int main() {
    string jobs[] = { "전사", "마법사", "도적", "궁수" };
    int job_choice = 0;
    string nickname;

    IPlayer* player = nullptr;

    cout << "* 닉네임을 입력해주세요: ";
    cin >> nickname;

    cout << "<전직 시스템>" << endl;
    cout << nickname << "님, 환영합니다!" << endl;
    cout << "* 원하시는 직업을 선택해주세요." << endl;

    for (int i = 0; i < 4; i++) {
        cout << (i + 1) << ". " << jobs[i] << endl;
    }

    while (player == nullptr)
    {
        cout << "선택: ";
        cin >> job_choice;

        switch (job_choice) {
        case 1:
            player = new CWarrior(nickname);
            break;
        case 2:
            player = new CMagician(nickname);
            break;
        case 3:
            player = new CThief(nickname);
            break;
        case 4:
            player = new CArcher(nickname);
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
            break;
        }
    }

    player->PrintPlayerStatus();
    
    CMonster* pMonster = nullptr;
    pMonster = new CMonster("고블린");
    
    while (pMonster)
    {
        player->Attack(pMonster);
        int monHP = pMonster->GetHP();
        if (monHP > 0)
        {
            pMonster->Attack(player);
        }
        else
        {
            delete pMonster;
            pMonster = nullptr;
        }
    }

    if (player != nullptr)
    {
        delete player;
    }


    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
