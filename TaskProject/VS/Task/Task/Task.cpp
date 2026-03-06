// Task.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h>  //  _getch() 함수를 사용하기 위해



int SetHPMPfromInput(int* hp, int* mp)
{
    int inputHP;
    int inputMP;
    printf("설정하려는 HP와 MP를 입력하세요 (51이상) :");
    scanf_s("%d %d", &inputHP, &inputMP);

    if (inputHP <= 50 || inputMP <= 50)
    {   //  잘못된 입력입니다
        return 1;
    }

    *hp = inputHP;
    *mp = inputMP;

    return 0;
}

int SetAtkDefFromInput(int* atk, int* def)
{
    int inputATK;
    int inputDEF;
    printf("설정하려는 ATK와 DEF를 입력하세요 (1이상) :");
    scanf_s("%d %d", &inputATK, &inputDEF);

    if (inputATK <= 0 || inputDEF <= 0)
    {   //  잘못된 입력입니다
        return 1;
    }

    *atk = inputATK;
    *def = inputDEF;

    return 0;
}

void SetPotion(int count, int* p_HPPotion, int* p_MPPotion)
{   // 각 포션의 수를 count만큼 지정합니다
    *p_HPPotion = count;
    *p_MPPotion = count;
}

void AddPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    *p_HPPotion += count;
    *p_MPPotion += count;
}

int MainMenu(int status[4])
{
    int result = 1;
    int HPPotion = 0;
    int MPPotion = 0;
    int level = 0;
    int exp = 0;
    SetPotion(5, &HPPotion, &MPPotion);
    while (result > 0)
    {
        printf("\n→ 1.HP UP / 2.MP UP / 3.공격력 UP / 4.방어력 UP / 5.현재 능력치 / 6.Level Up / 0.나가기 \n");
        
        int input = 0;
        //  입력을 받습니다
        input = _getch();   //  입력된 키 하나의 아스키 코드 값을 반환합니다

        switch (input)
        {
        case '1':
            //  체력증가
            if (HPPotion > 0)
            {
                status[0] += 20;
                HPPotion--;

                printf("HP Increased! HP : %d   남은 체력 포션 : %d\n", status[0], HPPotion);
            }
            else
            {
                printf("포션의 수가 부족합니다.\n");
            }
            break;
        case '2':
            //  마나증가
            if (MPPotion > 0)
            {
                status[1] += 30;
                MPPotion--;

                printf("MP Increased! MP : %d   남은 마나 포션 : %d\n", status[1], MPPotion);
            }
            else
            {
                printf("포션의 수가 부족합니다.\n");
            }
            break;
        case '3':
            //  ATK UP
            status[2] *= 2;

            printf("ATK Increased (%d)\n", status[2]);
            break;
        case '4':
            //  DEF UP
            status[3] += status[3];

            printf("DEF Increased (%d)\n", status[3]);
            break;
        case '5':
            //  Show my status
            printf("HP : %d / MP : %d / ATK : %d / DEF : %d / LEVEL : %d\n", status[0], status[1], status[2], status[3], level);
            printf("남은 포션의 수 : HP %d / MP : %d\n", HPPotion, MPPotion);
            break;
        case '6':
            //  Level UP
            if (exp < 5)
            {   //  6회까지는 경험치만 준다
                exp++;
                printf("경험치 증가!    EXP : %d\n", exp);
            }
            else
            {   //  6회 달성!
                exp = 0;
                level++;
                AddPotion(1, &HPPotion, &MPPotion);
                printf("레벨 업!  현재 레벨 : %d   포션이 지급되었습니다.\n", level);
            }
            break;
        case '0':
            // Exit
            printf("게임을 종료합니다\n");
            return 0;   //  이중 break를 사용할 수 없으니 그냥 리턴... switch...case문을 함수로 감싸면 되긴 하지만 귀찮으므로...
        default:
            printf("잘못된 입력입니다\n");
            break;
        }

    }

    return result;
}

int main()
{
    int Status[4] = { 0, }; //  HP, MP, ATK, DEF

    int result = 1;
    
    while (result)
    {
        result = SetHPMPfromInput(&Status[0], &Status[1]);

        if (result)
        {
            printf("잘못된 입력입니다. HP와 MP는 반드시 50을 넘어야 합니다.\n");
        }
    }
    
    result = 1;
    while (result)
    {
        result = SetAtkDefFromInput(&Status[2], &Status[3]);

        if (result)
        {
            printf("잘못된 입력입니다. ATK와 DEF는 1 이상이어야 합니다.\n");
        }
    }

    result = MainMenu(Status);

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

