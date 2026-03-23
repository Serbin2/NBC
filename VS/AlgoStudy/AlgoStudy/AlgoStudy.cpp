// AlgoStudy.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Picnic.h"
#include "BoardCover.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>

// Main.cpp

#include <iostream>

int FindMax(const int Arr[], int N)
{
	int Max = Arr[0];

	for (int i = 1; i <= N; i++)
	{
		if (Max < Arr[i])
		{
			Max = Arr[i];
		}
	}

	return Max;
}

int main(void)
{
	int Data[5] = { 3, 7, 2, 9, 1 };

	int Max = FindMax(Data, 5);
	std::cout << "Max = " << Max << std::endl;

	return 0;
}





// =====================================================
// Week02: 데이터를 담는 그릇 -- Vector
// =====================================================
// 이번 회차의 핵심: vector의 내부 동작 원리 이해하기
// - size와 capacity의 차이, 재할당 시점 관찰
// - push_back vs insert(앞) 시간 비교
// - vector 기본기 (선언, 순회, 수정)
// - 게임 인벤토리 종합 예제
// - 조건 필터링 패턴 비교
// =====================================================

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// =====================================================
// 예제 1: "가방이 커지는 순간" -- size와 capacity 관찰
// =====================================================
//#define RUN_WEEK02_EXAMPLE01
#ifdef RUN_WEEK02_EXAMPLE01
int main() {
	cout << "===== [예제 1] size와 capacity 관찰 =====" << endl;
	cout << endl;

	// --- Part A: 재할당이 일어나는 과정 관찰 ---
	cout << "[Part A] push_back을 반복하며 size/capacity 변화 관찰" << endl;
	cout << endl;

	vector<int> v;
	int prevCapacity = 0;  // 이전 capacity를 기억해둡니다

	for (int i = 1; i <= 20; i++) {
		v.push_back(i);  // 뒤에 추가 -- 평균 O(1)

		cout << "push_back(" << i << ")  →  "
			<< "size: " << v.size()
			<< ",  capacity: " << v.capacity();

		// capacity가 바뀌었다면 재할당이 발생한 것!
		if ((int)v.capacity() != prevCapacity) {
			cout << "  *** 재할당 발생! "
				<< prevCapacity << " -> " << v.capacity()
				<< " ***";
			prevCapacity = (int)v.capacity();
		}
		cout << endl;
	}

	cout << endl;
	cout << "=> capacity가 1 -> 2 -> 4 -> 8 -> 16 -> 32 ... "
		<< "2배씩 증가하는 패턴을 확인하세요!" << endl;

	// --- Part B: reserve로 재할당 방지 ---
	cout << endl;
	cout << "[Part B] reserve(20)을 사용하면 재할당이 발생하지 않습니다" << endl;
	cout << endl;

	vector<int> v2;
	v2.reserve(20);  // 미리 20칸 확보! -- 재할당 방지
	cout << "reserve(20) 직후  →  size: " << v2.size()
		<< ",  capacity: " << v2.capacity() << endl;
	cout << endl;

	int prevCapacity2 = (int)v2.capacity();
	bool reallocationOccurred = false;

	for (int i = 1; i <= 20; i++) {
		v2.push_back(i);

		if ((int)v2.capacity() != prevCapacity2) {
			reallocationOccurred = true;
			prevCapacity2 = (int)v2.capacity();
		}
	}

	cout << "20개 push_back 완료  →  size: " << v2.size()
		<< ",  capacity: " << v2.capacity() << endl;

	if (!reallocationOccurred) {
		cout << "=> 재할당이 한 번도 일어나지 않았습니다!" << endl;
	}

	cout << endl;
	cout << "결론: 크기를 미리 알면 reserve()로 재할당 비용을 아예 없앨 수 있습니다." << endl;

	return 0;
}
#endif

// =====================================================
// 예제 2: "뒤에 넣기 vs 앞에 넣기" -- 시간 비교
// =====================================================
//#define RUN_WEEK02_EXAMPLE02
#ifdef RUN_WEEK02_EXAMPLE02
int main() {
	cout << "===== [예제 2] push_back vs insert(앞) 시간 비교 =====" << endl;
	cout << endl;

	// 테스트할 데이터 크기들
	vector<int> sizes = { 10000, 50000, 100000 };

	for (int n : sizes) {
		cout << "--- n = " << n << " ---" << endl;

		// [A] push_back을 n번 수행 -- O(1) x n = O(n)
		{
			vector<int> v;
			v.reserve(n);  // 재할당 비용을 제거하고 순수 삽입 비용만 측정

			auto start = chrono::high_resolution_clock::now();

			for (int i = 0; i < n; i++) {
				v.push_back(i);  // 뒤에 추가 -- O(1)
			}

			auto end = chrono::high_resolution_clock::now();
			double ms = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;

			// 결과를 출력해서 컴파일러 최적화 방지
			cout << "  push_back x " << n << "  →  " << ms << " ms"
				<< "  (마지막 값: " << v.back() << ")" << endl;
		}

		// [B] insert(v.begin(), x)를 n번 수행 -- O(n) x n = O(n^2)
		{
			vector<int> v;

			auto start = chrono::high_resolution_clock::now();

			for (int i = 0; i < n; i++) {
				v.insert(v.begin(), i);  // 앞에 삽입 -- O(n), 뒤의 원소를 전부 밀어야 하므로
			}

			auto end = chrono::high_resolution_clock::now();
			double ms = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;

			// 결과를 출력해서 컴파일러 최적화 방지
			cout << "  insert(앞) x " << n << "  →  " << ms << " ms"
				<< "  (첫 번째 값: " << v.front() << ")" << endl;
		}

		cout << endl;
	}

	cout << "push_back은 n에 비례(O(n))하지만," << endl;
	cout << "insert(앞)는 n^2에 비례(O(n^2))하여 폭발적으로 느려집니다!" << endl;
	cout << endl;
	cout << "1회차에서 'O(n^2)은 n=10,000 정도까지'라고 했죠?" << endl;
	cout << "insert(앞)가 딱 그 케이스입니다." << endl;

	return 0;
}
#endif

// =====================================================
// 예제 3: "vector 기본기" -- 선언, 순회, 수정
// =====================================================
//#define RUN_WEEK02_EXAMPLE03
#ifdef RUN_WEEK02_EXAMPLE03
int main() {
	cout << "===== [예제 3] vector 기본기 =====" << endl;
	cout << endl;

	// --- 다양한 선언 방법 ---
	cout << "[선언 방법]" << endl;

	vector<int> v1;                    // 빈 vector
	vector<int> v2(5);                 // 크기 5, 모두 0으로 초기화
	vector<int> v3(5, 10);             // 크기 5, 모두 10으로 초기화
	vector<int> v4 = { 1, 2, 3, 4, 5 };  // 초기화 리스트

	cout << "v1 (빈 vector)       →  size: " << v1.size() << endl;

	cout << "v2 (크기 5, 0 초기화) →  ";
	for (int x : v2) cout << x << " ";
	cout << endl;

	cout << "v3 (크기 5, 10 초기화)→  ";
	for (int x : v3) cout << x << " ";
	cout << endl;

	cout << "v4 (초기화 리스트)    →  ";
	for (int x : v4) cout << x << " ";
	cout << endl;

	// --- 세 가지 순회 방법 비교 ---
	cout << endl;
	cout << "[순회 방법 비교]" << endl;
	vector<int> nums = { 10, 20, 30, 40, 50 };

	// 방법 1: 인덱스 for문 -- 인덱스 자체가 필요할 때
	cout << "인덱스 for문:       ";
	for (int i = 0; i < (int)nums.size(); i++) {
		cout << "nums[" << i << "]=" << nums[i] << "  ";
	}
	cout << endl;

	// 방법 2: 범위 기반 for -- 읽기만 할 때 (가장 간결)
	cout << "범위 기반 for:      ";
	for (int x : nums) {
		cout << x << " ";
	}
	cout << endl;

	// 방법 3: 범위 기반 for + 참조 -- 원소를 직접 수정할 때
	cout << "참조로 2배 수정:    ";
	for (int& x : nums) {
		x *= 2;  // 원본이 직접 수정됨!
	}
	for (int x : nums) {
		cout << x << " ";
	}
	cout << endl;

	cout << endl;
	cout << "원칙: 읽기 = for(int x : v), 수정 = for(int& x : v)" << endl;

	return 0;
}
#endif

// =====================================================
// 예제 4: "인벤토리 관리" -- 게임 시나리오 종합 예제
// =====================================================
//#define RUN_WEEK02_EXAMPLE04
#ifdef RUN_WEEK02_EXAMPLE04

// 인벤토리 아이템 구조체 (포인터 없이 값 시맨틱으로!)
struct Item {
	string name;
	int count;
};

// 인벤토리 전체 출력 함수
void printInventory(const vector<Item>& inventory) {
	cout << "┌─────────────────────────┐" << endl;
	cout << "│       인벤토리          │" << endl;
	cout << "├─────────────────────────┤" << endl;
	if (inventory.empty()) {
		cout << "│  (비어 있음)            │" << endl;
	}
	else {
		for (const Item& item : inventory) {  // 읽기만 하므로 const 참조
			cout << "│  " << item.name << " x" << item.count;
			// 간단한 정렬을 위한 패딩
			int padding = 22 - (int)item.name.size() - to_string(item.count).size() - 2;
			for (int i = 0; i < padding; i++) cout << " ";
			cout << " │" << endl;
		}
	}
	cout << "└─────────────────────────┘" << endl;
}

int main() {
	cout << "===== [예제 4] 인벤토리 관리 =====" << endl;
	cout << endl;

	vector<Item> inventory;

	// 1. 아이템 획득 -- push_back으로 뒤에 추가 (O(1))
	cout << "[아이템 획득]" << endl;
	inventory.push_back({ "체력 포션", 3 });   // O(1)
	inventory.push_back({ "마나 포션", 2 });   // O(1)
	inventory.push_back({ "해독제", 1 });      // O(1)
	inventory.push_back({ "골드 열쇠", 1 });   // O(1)

	printInventory(inventory);

	// 2. 아이템 사용 -- 인덱스 접근으로 수량 감소 (O(1))
	cout << endl;
	cout << "[체력 포션 사용!]" << endl;
	inventory[0].count--;  // O(1) -- 인덱스 접근
	cout << "체력 포션 남은 수량: " << inventory[0].count << endl;

	// 3. 아이템 소진 -- 수량이 0이면 제거
	cout << endl;
	cout << "[해독제 사용! (마지막 1개)]" << endl;
	inventory[2].count--;  // O(1) -- 인덱스 접근

	if (inventory[2].count == 0) {
		cout << "해독제 소진! 인벤토리에서 제거합니다." << endl;
		cout << "(erase 전 인벤토리 크기: " << inventory.size() << ")" << endl;

		// erase(중간) -- O(n), 뒤의 원소가 앞으로 밀려옴
		inventory.erase(inventory.begin() + 2);

		cout << "(erase 후 인벤토리 크기: " << inventory.size() << ")" << endl;
		cout << "=> '골드 열쇠'가 한 칸 앞으로 밀려왔습니다 (O(n) 작업!)" << endl;
	}

	cout << endl;
	printInventory(inventory);

	// 4. 전체 순회하며 조회 -- 범위 기반 for
	cout << endl;
	cout << "[2개 이상 보유 중인 아이템]" << endl;
	for (const Item& item : inventory) {  // O(n) -- 전체 순회
		if (item.count >= 2) {
			cout << "  " << item.name << " (" << item.count << "개)" << endl;
		}
	}

	return 0;
}
#endif

// =====================================================
// 예제 5 (도전): "조건 필터링" -- erase vs 새 vector 패턴
// =====================================================
//#define RUN_WEEK02_EXAMPLE05
#ifdef RUN_WEEK02_EXAMPLE05
int main() {
	cout << "===== [예제 5] 조건 필터링: erase vs 새 vector =====" << endl;
	cout << endl;

	vector<int> data = { 3, -1, 5, -2, 0, -7, 4, 8, -3, 2 };

	cout << "원본: ";
	for (int x : data) cout << x << " ";
	cout << endl;
	cout << "목표: 양수(> 0)만 남기기" << endl;
	cout << endl;

	// --- 방법 1: erase로 원본에서 삭제 ---
	// 주의: 중간 삭제는 O(n)이고, 이것을 반복하면 O(n^2)!
	cout << "[방법 1] erase로 원본에서 삭제" << endl;
	{
		vector<int> v = data;  // 원본 복사

		// 뒤에서부터 순회해야 인덱스가 꼬이지 않습니다
		for (int i = (int)v.size() - 1; i >= 0; i--) {
			if (v[i] <= 0) {
				v.erase(v.begin() + i);  // O(n) -- 뒤의 원소를 전부 당겨야 함
			}
		}

		cout << "결과: ";
		for (int x : v) cout << x << " ";
		cout << endl;
		cout << "=> erase를 여러 번 호출 → 최악 O(n^2)" << endl;
	}

	cout << endl;

	// --- 방법 2: 새 vector에 조건 맞는 것만 push_back ---
	// 원본을 수정하지 않고, 깔끔하게 O(n)으로 완료!
	cout << "[방법 2] 새 vector에 push_back (권장!)" << endl;
	{
		vector<int> v = data;  // 원본 복사
		vector<int> result;

		for (int x : v) {
			if (x > 0) {
				result.push_back(x);  // O(1) -- 뒤에 추가만 하면 됨
			}
		}

		cout << "결과: ";
		for (int x : result) cout << x << " ";
		cout << endl;
		cout << "=> push_back만 사용 → O(n)" << endl;
	}

	cout << endl;
	cout << "결론: 조건 필터링은 '새 vector에 담기' 패턴이 더 빠르고 안전합니다." << endl;
	cout << "원본을 수정하지 않아서 실수할 여지도 적거든요." << endl;

	return 0;
}
#endif

/*
int main()
{
	std::cout << "Hello World!\n";


	int numOfStudent = 6;

	int friendsList[10][2] = { {0,1},{0,2},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{3,5},{4,5} };

	int out = picnic(numOfStudent, friendsList);
	std::cout<< out;
	std::cout<<std::endl;

  
	//  보드커버 테스트용 입력 만들기
	std::vector<std::vector<int>> board;

	for (int i = 0; i < 10; i++)
	{
		std::vector<int> line;
		for (int j = 0; j < 8; j++)
		{
			if (j == 0 || j == 7 || i == 0 || i == 9)
			{
				line.push_back(1);
			}
			else
			{
				line.push_back(0);
			}
		}
		board.push_back(line);
	}

	int bcOut = 0;
	bcOut = BoardCover(board);

	std::cout << bcOut;
	std::cout << std::endl;


}*/

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
