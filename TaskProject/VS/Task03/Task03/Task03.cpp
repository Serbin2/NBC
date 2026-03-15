// Task03.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "Inventory.h"
#include "Item.h"

int main()
{
    TInventory<CItem> inven(5);

    CItem item01("card", 10);
    CItem item02("Keyring", 20);
    CItem item03("Trash", 0);
    CItem item04("Coffee", 7);
    CItem item05("Box", 1);
    CItem item06("Neckless", 50);
    CItem item07("Knife", 12);
    CItem item08("Candle", 3);

    inven.RemoveLastItem();

    inven.AddItem(item01);
    inven.AddItem(item02);
    inven.AddItem(item03);
    inven.AddItem(item04);
    inven.AddItem(item05);

    inven.PrintAllItems();
    //  resize 발생
    inven.AddItem(item06);
    inven.AddItem(item07);
    inven.AddItem(item08);

    inven.PrintAllItems();
    inven.SortItems();
    std::cout << "정렬" << std::endl;
    inven.PrintAllItems();

	//	복사 생성자 사용
	TInventory<CItem> copyInven(inven);
	copyInven.PrintAllItems();

	//	Assign 함수 사용
	copyInven.Assign(inven);
	copyInven.PrintAllItems();

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
