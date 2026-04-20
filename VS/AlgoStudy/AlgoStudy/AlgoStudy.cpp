// AlgoStudy.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#include <iostream>
//#include "Picnic.h"
//#include "BoardCover.h"
//
//#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <math.h>
//#include <vector>
//#include <bitset>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class A
{
	int a;
	int b;
};

struct B : A
{
	//B() { a = 1; };
	int c;
	int d;
};

class C : B
{
	C() { c = 2; };
	int e;
	int v;
};


int main() {

	vector<int> line(3);
	cin >> line[0] >> line[1] >> line[2];
	sort(line.begin(), line.end(), greater<>());

	string str;
	if (line[0] >= line[1] + line[2])
	{
		str = "Invalid";
	}
	else if (line[0] == line[1] && line[1] == line[2])
	{
		str = "Equilateral";
	}
	else if (line[0] == line[1] || line[1] == line[2] || line[0] == line[2])
	{
		str = "Isosceles";
	}
	else
	{
		str = "Scalene";
	}
	cout << str;


	return 0;
}


#pragma once
// =====================================================
// Week06: 어떤 도구를 꺼낼 것인가 -- 자료구조 선택의 기술
// =====================================================
// 이번 회차의 핵심: 같은 문제를 여러 자료구조로 풀어보며 선택 감각 기르기
// - Level 1 자료구조 총정리 -- 한눈에 비교
// - 시나리오 1: 출석부 -- 검색 빈도가 도구 선택을 좌우한다
// - 시나리오 2: Undo -- 성능이 같으면 의도를 더 잘 표현하는 도구
// - 시나리오 3: 매출 집계 -- 복합 요구사항의 트레이드오프
// - 도구 선택의 세 가지 기준: 성능, 의도 표현, 요구사항 매칭
// =====================================================

//#include <iostream>
//#include <string>
//#include <vector>
//#include <stack>
//#include <queue>
//#include <map>
//#include <set>
//#include <unordered_map>
//#include <unordered_set>
//#include <algorithm>
//using namespace std;

// Week06: 어떤 도구를 꺼낼 것인가 -- 자료구조 선택의 기술
//#define RUN_WEEK06_EXAMPLE01    // Level 1 도구함 총정리 (자료구조별 비교 데모)
//#define RUN_WEEK06_EXAMPLE02    // 출석부 관리 (vector vs set vs unordered_set)
//#define RUN_WEEK06_EXAMPLE03    // Undo 기능 (vector vs stack)
//#define RUN_WEEK06_EXAMPLE04    // 편의점 매출 집계 (vector vs map vs unordered_map)
//#define RUN_WEEK06_EXAMPLE05    // 도구 선택 가이드 + Level 2 맛보기



// =====================================================
// 예제 1: "Level 1 도구함 총정리" -- 자료구조별 특성 비교 데모
// =====================================================
#ifdef RUN_WEEK06_EXAMPLE01
int main() {
	cout << "===== [예제 1] Level 1 도구함 총정리 =====" << endl;
	cout << endl;

	// 같은 데이터: 3, 1, 4, 1, 5
	// 같은 데이터를 넣어도 자료구조마다 꺼내는 규칙이 다르다!
	cout << "같은 데이터 {3, 1, 4, 1, 5}를 각 자료구조에 넣어봅니다." << endl;
	cout << endl;

	// ── 1) vector: 인덱스로 자유롭게 접근 ──
	cout << "[1] vector -- 순서 있는 연속 배열" << endl;

	vector<int> v = { 3, 1, 4, 1, 5 };

	// vector: 인덱스로 자유롭게 접근 -- O(1)
	cout << "  넣은 순서 그대로 저장: ";
	for (int i = 0; i < (int)v.size(); i++) {
		cout << "v[" << i << "]=" << v[i] << " ";
	}
	cout << endl;
	cout << "  → 인덱스로 아무 위치나 접근 가능. v[2] = " << v[2] << endl;
	cout << "  → 접근 O(1), 검색 O(n), 끝 삽입/삭제 O(1)" << endl;
	cout << endl;

	// ── 2) stack: 마지막에 넣은 것만 꺼낼 수 있다 ──
	cout << "[2] stack -- LIFO (후입선출)" << endl;

	stack<int> st;
	for (int n : {3, 1, 4, 1, 5}) st.push(n);

	// stack: 마지막에 넣은 것만 꺼낼 수 있다 -- LIFO
	cout << "  꺼내는 순서 (top → pop 반복): ";
	while (!st.empty()) {
		cout << st.top() << " ";   // 마지막에 넣은 것부터 나온다!
		st.pop();
	}
	cout << endl;
	cout << "  → 5, 1, 4, 1, 3 순서! 넣은 순서의 역순" << endl;
	cout << "  → push/pop O(1). top만 접근 가능" << endl;
	cout << endl;

	// ── 3) queue: 먼저 넣은 것부터 꺼낸다 ──
	cout << "[3] queue -- FIFO (선입선출)" << endl;

	queue<int> q;
	for (int n : {3, 1, 4, 1, 5}) q.push(n);

	// queue: 먼저 넣은 것부터 꺼낸다 -- FIFO
	cout << "  꺼내는 순서 (front → pop 반복): ";
	while (!q.empty()) {
		cout << q.front() << " ";  // 먼저 넣은 것부터 나온다!
		q.pop();
	}
	cout << endl;
	cout << "  → 3, 1, 4, 1, 5 순서! 넣은 순서 그대로" << endl;
	cout << "  → push/pop O(1). front만 접근 가능" << endl;
	cout << endl;

	// ── 4) set: 중복 제거 + 자동 정렬 ──
	cout << "[4] set -- 중복 제거 + 자동 정렬" << endl;

	set<int> s = { 3, 1, 4, 1, 5 };

	// set: 중복 제거 + 자동 정렬
	cout << "  저장된 내용: ";
	for (int n : s) cout << n << " ";
	cout << endl;
	cout << "  → {3, 1, 4, 1, 5} 중 중복(1)이 제거되고, 정렬됨!" << endl;
	cout << "  → size: 5개 넣었지만 " << s.size() << "개만 저장" << endl;
	cout << "  → 검색/삽입/삭제 O(log n)" << endl;
	cout << endl;

	// ── 5) map: key로 value에 접근 ──
	cout << "[5] map -- key로 value에 접근" << endl;

	// map: key로 value에 접근
	map<string, int> m;
	m["세번째"] = 3;
	m["첫번째"] = 1;
	m["네번째"] = 4;
	m["다섯번째"] = 5;

	cout << "  key로 접근: m[\"세번째\"] = " << m["세번째"] << endl;
	cout << "  순회 (key 정렬순): ";
	for (auto& p : m) {
		cout << p.first << "=" << p.second << " ";
	}
	cout << endl;
	cout << "  → key 기준 정렬. 검색/삽입/삭제 O(log n)" << endl;
	cout << endl;

	// ── 정리 ──
	cout << "========================================" << endl;
	cout << "[정리] 같은 데이터를 담아도, 꺼내는 규칙이 다르다!" << endl;
	cout << "  vector → 인덱스로 자유롭게" << endl;
	cout << "  stack  → 마지막부터 (LIFO)" << endl;
	cout << "  queue  → 처음부터 (FIFO)" << endl;
	cout << "  set    → 중복 제거 + 정렬" << endl;
	cout << "  map    → key라는 이름표로 접근" << endl;

	return 0;
}
#endif

// =====================================================
// 예제 2: "출석부 관리" -- vector vs set vs unordered_set
// =====================================================
#ifdef RUN_WEEK06_EXAMPLE02
int main() {
	cout << "===== [예제 2] 출석부 관리 -- vector vs set vs unordered_set =====" << endl;
	cout << endl;

	// 출석한 학생 명단 (5명)
	vector<string> attendList = { "김철수", "박영희", "이민수", "정하나", "최준호" };

	// 확인할 학생
	string target = "정하나";

	// ── 1) vector 방식 ──
	cout << "[1] vector<string> -- 순회하며 비교" << endl;
	{
		vector<string> attended;
		for (auto& name : attendList) {
			attended.push_back(name);
		}

		// vector: 순회하며 비교 -- O(n)
		// 처음부터 하나씩 확인해야 한다
		bool found = false;
		int compareCount = 0;
		for (auto& name : attended) {
			compareCount++;
			if (name == target) {
				found = true;
				break;
			}
		}
		cout << "  \"" << target << "\" 출석 여부: " << (found ? "O" : "X") << endl;
		cout << "  비교 횟수: " << compareCount << "번 (최악 " << attended.size() << "번)" << endl;
		cout << "  시간 복잡도: O(n)" << endl;

		// 중복 방지? 직접 구현해야 한다!
		cout << "  중복 방지: 직접 구현 필요" << endl;
		cout << "  정렬: 없음" << endl;
	}
	cout << endl;

	// ── 2) set 방식 ──
	cout << "[2] set<string> -- 트리 탐색" << endl;
	{
		set<string> attended;
		for (auto& name : attendList) {
			attended.insert(name);
		}

		// set: 트리 탐색 -- O(log n)
		// count()로 존재 여부를 빠르게 확인
		bool found = attended.count(target) > 0;
		cout << "  \"" << target << "\" 출석 여부: " << (found ? "O" : "X") << endl;
		cout << "  시간 복잡도: O(log n) -- 5명 중 ~3번 비교면 충분" << endl;

		// set은 중복 자동 방지 + 정렬
		cout << "  중복 방지: 자동!" << endl;
		cout << "  정렬: 자동! → ";
		for (auto& name : attended) cout << name << " ";
		cout << endl;
	}
	cout << endl;

	// ── 3) unordered_set 방식 ──
	cout << "[3] unordered_set<string> -- 해시 접근" << endl;
	{
		unordered_set<string> attended;
		for (auto& name : attendList) {
			attended.insert(name);
		}

		// unordered_set: 해시 접근 -- O(1) 평균
		// 해시 함수로 바로 위치를 계산해서 즉시 확인
		bool found = attended.count(target) > 0;
		cout << "  \"" << target << "\" 출석 여부: " << (found ? "O" : "X") << endl;
		cout << "  시간 복잡도: O(1) 평균 -- 데이터가 얼마나 많든 즉시!" << endl;

		cout << "  중복 방지: 자동!" << endl;
		cout << "  정렬: 없음 (순서 보장 안 됨) → ";
		for (auto& name : attended) cout << name << " ";
		cout << endl;
	}
	cout << endl;

	// ── 비교 정리 ──
	cout << "========================================" << endl;
	cout << "[비교 정리]" << endl;
	cout << "  ┌────────────────┬──────────┬──────────┬───────────────┐" << endl;
	cout << "  │                │  vector  │   set    │ unordered_set │" << endl;
	cout << "  ├────────────────┼──────────┼──────────┼───────────────┤" << endl;
	cout << "  │ 검색 속도      │  O(n)    │ O(log n) │  O(1) 평균    │" << endl;
	cout << "  │ 중복 방지      │  직접    │  자동    │  자동         │" << endl;
	cout << "  │ 정렬           │  없음    │  자동    │  없음         │" << endl;
	cout << "  └────────────────┴──────────┴──────────┴───────────────┘" << endl;
	cout << endl;
	// → 검색 빈도가 높을수록 set 계열이 유리!
	cout << "→ 검색 빈도가 높을수록 set 계열이 유리!" << endl;
	cout << "→ 정렬 필요 없으면 unordered_set이 최적!" << endl;

	return 0;
}
#endif

// =====================================================
// 예제 3: "Undo 기능" -- vector vs stack
// =====================================================
#ifdef RUN_WEEK06_EXAMPLE03
int main() {
	cout << "===== [예제 3] Undo 기능 -- vector vs stack =====" << endl;
	cout << endl;

	// ── 1) vector 버전 ──
	cout << "[1] vector<char> -- push_back / pop_back" << endl;
	{
		vector<char> editor;

		// 문자 입력
		editor.push_back('H');
		editor.push_back('e');
		editor.push_back('l');
		editor.push_back('l');
		editor.push_back('o');

		cout << "  입력 후: ";
		for (char c : editor) cout << c;
		cout << endl;

		// Undo: pop_back으로 마지막 문자 제거 -- O(1)
		editor.pop_back();
		cout << "  Undo 1회: ";
		for (char c : editor) cout << c;
		cout << endl;

		editor.pop_back();
		cout << "  Undo 2회: ";
		for (char c : editor) cout << c;
		cout << endl;
		cout << "  → push_back/pop_back 모두 O(1). 잘 동작한다!" << endl;
		cout << endl;

		// ⚠️ 그런데 vector는 중간 접근이 가능하다 (위험!)
		// 둘 다 O(1) -- 성능은 동일
		// 그런데 vector는 중간 접근이 가능하다 (의도치 않은 수정 위험!)
		cout << "  ⚠️ vector의 위험: 중간 접근이 가능하다!" << endl;
		cout << "  현재: ";
		for (char c : editor) cout << c;
		cout << endl;

		// 실수로 중간 요소를 바꿔버릴 수 있다!
		editor[0] = 'X';   // Undo 로직과 무관한 수정이 가능!
		cout << "  editor[0] = 'X' 실행 후: ";
		for (char c : editor) cout << c;
		cout << endl;
		cout << "  → Undo와 무관하게 중간을 건드릴 수 있다. 버그의 원인!" << endl;
	}
	cout << endl;

	// ── 2) stack 버전 ──
	cout << "[2] stack<char> -- push / pop" << endl;
	{
		stack<char> editor;

		// 문자 입력
		editor.push('H');
		editor.push('e');
		editor.push('l');
		editor.push('l');
		editor.push('o');

		// stack은 순회할 수 없으므로 현재 상태를 보여주기 위해 복사
		auto showStack = [](stack<char> s) {
			string result;
			while (!s.empty()) {
				result = s.top() + result;
				s.pop();
			}
			return result;
			};

		cout << "  입력 후: " << showStack(editor) << endl;

		// Undo: pop으로 마지막 문자 제거 -- O(1)
		editor.pop();
		cout << "  Undo 1회: " << showStack(editor) << endl;

		editor.pop();
		cout << "  Undo 2회: " << showStack(editor) << endl;
		cout << "  → push/pop 모두 O(1). 역시 잘 동작한다!" << endl;
		cout << endl;

		// stack은 top만 접근 가능 -- 구조가 실수를 막아준다
		cout << "  ✅ stack의 장점: top만 접근 가능!" << endl;
		cout << "  editor.top() = '" << editor.top() << "' (마지막 문자만 볼 수 있다)" << endl;
		cout << "  editor[0] = 'X'? → 컴파일 에러! stack에는 [] 연산이 없다!" << endl;
		cout << "  → 구조가 실수를 막아준다. 의도치 않은 중간 수정이 불가능!" << endl;
	}
	cout << endl;

	// ── 비교 정리 ──
	cout << "========================================" << endl;
	cout << "[비교 정리]" << endl;
	cout << "  ┌────────────────┬──────────────┬──────────────┐" << endl;
	cout << "  │                │   vector     │    stack     │" << endl;
	cout << "  ├────────────────┼──────────────┼──────────────┤" << endl;
	cout << "  │ 추가/제거 성능 │   O(1)       │    O(1)      │" << endl;
	cout << "  │ 중간 접근      │   가능 (위험)│  불가 (안전) │" << endl;
	cout << "  │ 의도 표현      │   불명확     │ LIFO 명확    │" << endl;
	cout << "  └────────────────┴──────────────┴──────────────┘" << endl;
	cout << endl;
	// 코드는 미래의 나에게 보내는 편지. 의도를 담자
	cout << "→ 성능이 같다면, 의도를 더 잘 표현하는 도구를 고르자!" << endl;
	cout << "→ 코드는 미래의 나에게 보내는 편지. 의도를 담자." << endl;

	return 0;
}
#endif

// =====================================================
// 예제 4: "편의점 매출 집계" -- vector vs map vs unordered_map
// =====================================================
#ifdef RUN_WEEK06_EXAMPLE04
int main() {
	cout << "===== [예제 4] 편의점 매출 집계 -- vector vs map vs unordered_map =====" << endl;
	cout << endl;

	// 판매 기록 데이터
	vector<string> salesLog = {
		"콜라", "삼각김밥", "콜라", "커피", "삼각김밥",
		"콜라", "커피", "아이스크림", "삼각김밥", "콜라",
		"아이스크림", "커피", "콜라", "삼각김밥", "커피"
	};

	cout << "판매 기록: ";
	for (auto& item : salesLog) cout << item << " ";
	cout << endl;
	cout << "(총 " << salesLog.size() << "건)" << endl;
	cout << endl;

	// 요구사항:
	// (A) 각 상품이 몇 개 팔렸는지 집계
	// (B) 가장 많이 팔린 상품 찾기
	// (C) 전체 상품 목록을 이름순으로 출력

	// ── 1) vector<pair<string,int>> 방식 ──
	cout << "[1] vector<pair<string,int>> -- 직접 구현" << endl;
	{
		// vector: 직접 구현 -- 코드가 길지만 동작은 한다
		vector<pair<string, int>> salesVec;

		// (A) 집계: 매 상품마다 이미 있는지 순회 검색해야 한다!
		for (auto& item : salesLog) {
			bool found = false;
			// 이미 있는 상품인지 처음부터 순회하며 확인 -- O(n)
			for (auto& p : salesVec) {
				if (p.first == item) {
					p.second++;    // 있으면 +1
					found = true;
					break;
				}
			}
			if (!found) {
				salesVec.push_back({ item, 1 });  // 없으면 새로 추가
			}
		}

		cout << "  (A) 상품별 집계:" << endl;
		for (auto& p : salesVec) {
			cout << "      " << p.first << ": " << p.second << "개" << endl;
		}

		// (B) 최다 판매 상품
		string bestItem;
		int bestCount = 0;
		for (auto& p : salesVec) {
			if (p.second > bestCount) {
				bestItem = p.first;
				bestCount = p.second;
			}
		}
		cout << "  (B) 최다 판매: " << bestItem << " (" << bestCount << "개)" << endl;

		// (C) 이름순 출력 → 직접 정렬 필요!
		sort(salesVec.begin(), salesVec.end());
		cout << "  (C) 이름순: ";
		for (auto& p : salesVec) cout << p.first << " ";
		cout << endl;
		cout << "  → 코드가 길고, 검색/정렬을 직접 구현해야 한다" << endl;
	}
	cout << endl;

	// ── 2) map<string,int> 방식 ──
	cout << "[2] map<string,int> -- 카운팅 + 정렬 자동" << endl;
	{
		// map: 카운팅 + 정렬 -- 균형 잡힌 선택
		map<string, int> salesMap;

		// (A) 집계: m[key]++ 한 줄! (5회차 카운팅 패턴)
		for (auto& item : salesLog) {
			salesMap[item]++;   // 없으면 0으로 자동 생성 → +1
		}

		cout << "  (A) 상품별 집계 (이름순 자동 정렬!):" << endl;
		// (C) 이름순 출력: map은 key 기준 자동 정렬!
		for (auto& p : salesMap) {
			cout << "      " << p.first << ": " << p.second << "개" << endl;
		}

		// (B) 최다 판매 상품
		string bestItem;
		int bestCount = 0;
		for (auto& p : salesMap) {
			if (p.second > bestCount) {
				bestItem = p.first;
				bestCount = p.second;
			}
		}
		cout << "  (B) 최다 판매: " << bestItem << " (" << bestCount << "개)" << endl;
		cout << "  (C) 이름순 출력: 위 결과가 이미 이름순!" << endl;
		cout << "  → m[key]++ 한 줄로 집계 + 순회 시 자동 정렬. 깔끔!" << endl;
	}
	cout << endl;

	// ── 3) unordered_map<string,int> 방식 ──
	cout << "[3] unordered_map<string,int> -- 속도 최우선" << endl;
	{
		// unordered_map: 속도 최우선 -- 정렬이 필요하면 별도 처리
		unordered_map<string, int> salesUMap;

		// (A) 집계: 동일한 패턴, 하지만 O(1) 평균!
		for (auto& item : salesLog) {
			salesUMap[item]++;   // 해시 기반이라 삽입/접근 O(1) 평균
		}

		cout << "  (A) 상품별 집계 (정렬 안 됨!):" << endl;
		for (auto& p : salesUMap) {
			cout << "      " << p.first << ": " << p.second << "개" << endl;
		}

		// (B) 최다 판매 상품
		string bestItem;
		int bestCount = 0;
		for (auto& p : salesUMap) {
			if (p.second > bestCount) {
				bestItem = p.first;
				bestCount = p.second;
			}
		}
		cout << "  (B) 최다 판매: " << bestItem << " (" << bestCount << "개)" << endl;
		cout << "  (C) 이름순 출력: 별도 정렬이 필요! (unordered는 순서 보장 X)" << endl;
		cout << "  → 삽입/접근 O(1) 평균으로 가장 빠르지만, 정렬 불가" << endl;
	}
	cout << endl;

	// ── 비교 정리 ──
	cout << "========================================" << endl;
	cout << "[비교 정리]" << endl;
	cout << "  ┌────────────────┬────────────┬────────────┬───────────────┐" << endl;
	cout << "  │                │  vector    │   map      │ unordered_map │" << endl;
	cout << "  ├────────────────┼────────────┼────────────┼───────────────┤" << endl;
	cout << "  │ 집계 코드      │  △ 길다   │ ◎ 한 줄   │  ◎ 한 줄     │" << endl;
	cout << "  │ 집계 성능      │  O(n) 검색 │ O(log n)   │  O(1) 평균    │" << endl;
	cout << "  │ 이름순 출력    │  △ 직접   │ ◎ 자동    │  △ 별도 정렬  │" << endl;
	cout << "  │ 종합           │  △        │ ◎         │  ○            │" << endl;
	cout << "  └────────────────┴────────────┴────────────┴───────────────┘" << endl;
	cout << endl;
	cout << "→ 세 요구사항을 모두 만족하는 균형 잡힌 선택: map" << endl;
	cout << "→ 정렬 불필요 + 속도 최우선이면: unordered_map" << endl;

	return 0;
}
#endif

// =====================================================
// 예제 5: "도구 선택 가이드" -- 상황별 추천 + Level 2 맛보기
// =====================================================
#ifdef RUN_WEEK06_EXAMPLE05
int main() {
	cout << "===== [예제 5] 도구 선택 가이드 + Level 2 맛보기 =====" << endl;
	cout << endl;

	// ── Part A: 상황별 자료구조 추천 ──
	// Level 1 정리: 상황에 맞는 도구를 고르는 것이 첫걸음
	cout << "━━━ Part A: 상황별 자료구조 추천 ━━━" << endl;
	cout << endl;

	// 상황 → 추천 자료구조 매핑
	vector<pair<string, string>> guide = {
		{"순서대로 데이터를 담고 싶다",         "→ vector"},
		{"되돌리기 기능이 필요하다",            "→ stack (LIFO)"},
		{"대기열이 필요하다",                   "→ queue (FIFO)"},
		{"이름으로 데이터를 찾고 싶다",         "→ map / unordered_map"},
		{"중복을 제거하고 싶다",                "→ set / unordered_set"},
		{"정렬된 순서가 필요하다",              "→ map / set (unordered 아님!)"},
		{"속도가 최우선이다 (정렬 불필요)",     "→ unordered_map / unordered_set"},
	};

	cout << "  [상황별 도구 선택 가이드]" << endl;
	for (auto& g : guide) {
		cout << "  \"" << g.first << "\"" << endl;
		cout << "      " << g.second << endl;
	}
	cout << endl;

	cout << "  [선택의 세 가지 기준]" << endl;
	cout << "  1. 성능:      자주 하는 연산이 빠른 도구를 고른다" << endl;
	cout << "  2. 의도 표현: 코드를 읽는 사람이 의도를 알 수 있는 도구" << endl;
	cout << "  3. 요구사항:  정렬? 중복? key-value? → 기능이 맞는 도구" << endl;
	cout << endl;

	// ── Part B: Level 2 맛보기 ──
	// 그런데 아직 못 푼 문제가 있다...
	cout << "━━━ Part B: 아직 못 푼 문제 → Level 2 맛보기 ━━━" << endl;
	cout << endl;

	vector<int> data = { 38, 27, 43, 3, 9, 82, 10 };

	cout << "  데이터: ";
	for (int n : data) cout << n << " ";
	cout << endl;
	cout << endl;

	// 문제 1: 가장 큰 값 찾기
	cout << "  [문제] 가장 큰 값을 찾으려면?" << endl;

	// 지금 방법: 처음부터 끝까지 순회 -- O(n)
	int maxVal = data[0];
	for (int n : data) {
		if (n > maxVal) maxVal = n;
	}
	cout << "  지금 방법: 처음부터 끝까지 순회 → " << maxVal << " (O(n))" << endl;

	// 만약 데이터가 정렬되어 있다면?
	vector<int> sorted_data = data;
	sort(sorted_data.begin(), sorted_data.end());
	cout << "  정렬된 데이터: ";
	for (int n : sorted_data) cout << n << " ";
	cout << endl;
	cout << "  정렬되어 있다면? 맨 끝을 보면 됨 → " << sorted_data.back() << " (O(1)!)" << endl;
	cout << endl;

	// 문제 2: 특정 값 찾기
	cout << "  [문제] 특정 값(43)을 찾으려면?" << endl;

	// 지금 방법: 처음부터 순회 -- O(n)
	int target = 43;
	int count = 0;
	for (int n : data) {
		count++;
		if (n == target) break;
	}
	cout << "  지금 방법: 처음부터 순회 → " << count << "번 비교 (O(n))" << endl;

	// 정렬된 데이터에서 이진 탐색을 쓸 수 있다면?
	cout << "  정렬 + 이진 탐색이라면? → ~3번 비교면 충분 (O(log n)!)" << endl;
	cout << endl;

	// "정렬"과 "탐색" -- Level 2에서 만납니다!
	cout << "  ┌─────────────────────────────────────────────┐" << endl;
	cout << "  │  정렬하는 비용은 얼마나 들까?               │" << endl;
	cout << "  │  정렬된 데이터에서 빠르게 찾는 방법은?      │" << endl;
	cout << "  │                                             │" << endl;
	cout << "  │  → 이 질문들의 답은 Level 2에서 만납니다!   │" << endl;
	cout << "  └─────────────────────────────────────────────┘" << endl;
	cout << endl;

	cout << "========================================" << endl;
	cout << "Level 1 완주!" << endl;
	cout << "시간 복잡도(1회차) → 자료구조별 특성(2~5회차) → 도구 선택(6회차)" << endl;
	cout << "\"도구를 아는 것\"에서 \"도구를 고르는 것\"으로 성장했습니다." << endl;
	cout << "Level 2에서는 \"정렬\"과 \"탐색\"의 세계로 들어갑니다!" << endl;

	return 0;
}
#endif


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
