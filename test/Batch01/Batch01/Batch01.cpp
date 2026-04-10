// Batch01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#define BATCH01
//#define BATCH02
//#define BATCH03
//#define BATCH04
//#define BATCH05
//#define BATCH06
//#define BATCH07
//#define BATCH08
//#define BATCH09
//#define BATCH10
//#define BATCH11

using namespace std;

#ifdef BATCH01
//	배열의 합 구하기
#include <iostream>
#include <vector>
long long sum(const vector<int>& v)
{
	long long retval = 0;
	
	for (int i = 0; i < v.size(); i++)
	{
		retval = retval + v[i];
	}

	return retval;
}

int main() {
	vector<int> v{ 3, 6, 7, 9 };
	cout << sum(v) << "\\n"; // 25
}
#endif

#ifdef BATCH02
#include <iostream>
bool is_leap(int y) {
	//1. * *윤년 * *은 보통 4년마다 한 번씩 돌아옵니다. (즉, `연도가 4의 배수`이면 윤년)
	//2. * *100의 배수 * *인 해는 윤년에서 제외합니다.
	//3. * *400의 배수 * *인 해는 다시 윤년으로 인정합니다.
	if (y % 400 == 0)
	{	//	400의 배수
		return true;
	}
	if (y % 100 == 0)
	{	//	100의 배수
		return false;
	}
	if (y % 4 == 0)
	{	//	4의 배수
		return true;
	}
	//	나머지
	return false;
}

int main() {
	cout << boolalpha << is_leap(2000) << " " << is_leap(1900) << " " << is_leap(2024) << "\\n"; // true false true
}
#endif

//#define BATCH03
#ifdef BATCH03
//`class Rect`를 구현하시오.
//
//- private: `int width, height`
//	- 생성자 `(width, height)`
//	- `int area() const`
//	- `void setWidth(int)`, `void setHeight(int)` : 0 미만이면 0 저장
#include <iostream>
using namespace std;

class Rect {
public:
	Rect(int width, int height) :
		width(width), height(height)
	{
	}
	~Rect() {};
	
	int area() const
	{	//	영역의 크기?
		return width * height;
	}
	void setWidth(int w)
	{
		if (w < 0)	w = 0;
		width = w;
	}
	void setHeight(int h)
	{
		if (h < 0)	h = 0;
		height = h;
	}

private:
	int width;
	int height;

};

int main() {
	Rect r(3, 4);
	cout << r.area() << "\\n"; // 12
	r.setWidth(-5); r.setHeight(2);
	cout << r.area() << "\\n"; // 0
}
#endif

//#define BATCH04
#ifdef BATCH04
#include <iostream>
#include <string>
using namespace std;

class BankAccount 
{
private:
	string owner;
	double balance;

public:
	BankAccount(const string& name, double initial) {
		// 생성자 로직을 작성해주세요.
		// 생성자 매개변수 설명: 소유자 이름(name), 초기 잔액(initial)
		owner = name;
		balance = initial;
	}

	void deposit(double amount) {
		// 입금 로직을 작성해주세요.
		balance += amount;
	}

	bool withdraw(double amount) {
		// 출금 로직을 작성해주세요.
		if (balance < amount)	return false;
		balance -= amount;
		return true;
	}

	double getBalance() const {
		// 현재 잔액 반환 로직을 작성해주세요.
		return balance;
	}

	// 계좌 정보 출력하는 함수 (구현하실 필요 없음)
	void printInfo() const {
		cout << "Owner: " << owner << ", Balance: " << balance << " won\\n";
	}
};

int main() {
	BankAccount account("Alice", 1000);
	account.printInfo(); // Owner: Alice, Balance: 1000 won

	account.deposit(500);
	account.printInfo(); // Owner: Alice, Balance: 1500 won

	if (account.withdraw(2000)) {
		cout << "Withdraw OK!\\n"; // 이건 출력 안됨
	}
	else {
		cout << "Withdraw FAILED!\\n"; // 이것이 출력됨
	}

	if (account.withdraw(1000)) {
		cout << "Withdraw OK!\\n"; // 이것이 출력됨
	}

	account.printInfo(); // Owner: Alice, Balance: 500 won
}
#endif

//#define BATCH05
#ifdef BATCH05
///class Animal { virtual void speak(); }에서 파생 클래스 Dog, Cat를 만들고 각각 "Woof", "Meow"를 출력하도록 오버라이드하시오.Animal * 배열로 다형성 출력
#include <iostream>
#include <vector>
using namespace std;

class Animal 
{
public:
	virtual ~Animal() {};
	// 여기에 Animal 내용 작성해주세요.

	virtual void speak()
	{
		cout << "~~야생의 소리~~" << endl;
	}
};
// 여기에 Dog, Cat 클래스 작성해주세요.
class Dog : public Animal
{
public:
	~Dog() {};
	void speak() override
	{
		cout << "Woof" << endl;
	}
};

class Cat : public Animal
{
	~Cat() {};
	void speak() override
	{
		cout << "Meow" << endl;
	}
};


int main() {
	vector<Animal*> zoo{ new Dog, new Cat, new Animal };
	for (auto p : zoo) p->speak(); // Woof / Meow / ???
	for (auto p : zoo) delete p;
}
#endif

//#define BATCH06
#ifdef BATCH06
#include <iostream>
#include <string>
using namespace std;

template<typename T>
T get_max(T a, T b)
{
	if (a > b)	return a;
	return b;
}

int main() {
	cout << get_max(10, 20) << "\\n";            // 20
	cout << get_max(3.14, 2.71) << "\\n";        // 3.14
	string s1 = "Apple", s2 = "Banana";
	cout << get_max(s1, s2) << "\\n";            // Banana
}
#endif

//#define BATCH07
#ifdef BATCH07
#include <iostream>
using namespace std;

class IntPtr
{
	int* ptr;
public:
	IntPtr(int val) {
		ptr = new int(val);
	}

	~IntPtr() 
	{
		delete ptr;
	}

	IntPtr(const IntPtr& other)
	{
		ptr = new int(other.getValue());
	}

	int getValue() const
	{
		return *ptr;
	}
};

int main() {
	IntPtr p1(10);
	IntPtr p2 = p1; // 복사 생성자 호출

	cout << p1.getValue() << "\\n"; // 10
	cout << p2.getValue() << "\\n"; // 10
}
#endif

//#define BATCH08
#ifdef BATCH08
#include <iostream>
#include <unordered_map>
using namespace std;

vector<int> removeDuplicates(const vector<int>& v) 
{
	// 중복을 제거하고 순서를 유지한 벡터 반환
	// 예: [1,3,2,3,1,4] -> [1,3,2,4]
	vector<int> retvec;
	unordered_map<int,int> map;
	for (auto& i : v)
	{
		map[i]++;
		if (map[i] > 1)	continue;
		retvec.push_back(i);
	}
	return retvec;
}

int main() {
	vector<int> nums = { 1, 3, 2, 3, 1, 4, 2, 5 };
	vector<int> result = removeDuplicates(nums);

	cout << "Result: ";
	for (int n : result) {
		cout << n << " ";
	}
	cout << "\\n"; // 1 3 2 4 5
}
#endif

//#define BATCH09
#ifdef BATCH09
#include <iostream>
#include <string>
#include <unordered_map>
// 추가로 필요하다고 생각하는 헤더들은 여기다가 자유롭게 추가할 것
using namespace std;

int getMinChangesToAnagram(const string& s1, const string& s2) 
{
	// 여기에 답안을 작성해주세요.
	if (s1.length() != s2.length())	return -1;
	unordered_map<char, int> map;

	for (int i = 0; i < s1.length(); i++)
	{
		map[s1[i]]++;
	}

	for (int i = 0; i < s1.length(); i++)
	{
		map[s2[i]]--;
	}

	int answer = 0;
	for (auto i : map)
	{	//	양수인 것만 세기
		if (i.second > 0)
		{
			answer += i.second;
		}
	}
	return answer;
}

int main() {
	cout << "listen -> silent: " << getMinChangesToAnagram("listen", "silent") << "\\n"; // 0
	cout << "abc -> abd: " << getMinChangesToAnagram("abc", "abd") << "\\n"; // 1
	cout << "aabbcc -> aabdde: " << getMinChangesToAnagram("aabbcc", "aabdde") << "\\n"; // 3
	cout << "abc -> xyz: " << getMinChangesToAnagram("abc", "xyz") << "\\n"; // 3
	cout << "ab -> abc: " << getMinChangesToAnagram("ab", "abc") << "\\n"; // -1
	cout << "test -> test: " << getMinChangesToAnagram("test", "test") << "\\n"; // 0
}
#endif

#define BATCH10
#ifdef BATCH10
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Item
{
	string name;
	int attackPower;
	int rarity;

	// TODO: 요구사항에 맞는 비교 연산자 구현
	bool operator<(const Item& other) const
	{
		if (this->attackPower > other.attackPower)	return true;
		if (this->attackPower == other.attackPower)
		{
			if (this->rarity < other.rarity)	return true;
			else if (this->rarity == other.rarity)
			{
				if (this->name > other.name)	return true;
			}
		}
		return false;
	}
};

// TODO: 조건부 삽입 및 가격 갱신 함수 구현
void tryInsert(map<Item, int>& shop, const Item& item, int price)
{
	if (item.attackPower < 50)	return;

	auto a = shop.find(item);
	if (a != shop.end())
	{
		if (a->second >= price)	return;
		a->second = price;
	}
	else
	{
		shop[item] = price;
	}
}

int main()
{
	map<Item, int> shop;

	tryInsert(shop, { "Excalibur",      100,    1 }, 5000);
	tryInsert(shop, { "Dragon Sword",   100,    2 }, 4500);
	tryInsert(shop, { "Wooden Sword",   20,     5 }, 100);
	tryInsert(shop, { "Excalibur",      100,    1 }, 5200);
	tryInsert(shop, { "Excalibur",      100,    1 }, 4800);

	cout << "--- 상점 아이템 목록 (정렬 및 갱신 결과) ---\n";
	for (const auto& kv : shop)
	{
		const Item& item = kv.first;
		int price = kv.second;

		cout << item.name << " [ATK: " << item.attackPower
			<< ", Rarity: " << item.rarity << "] : Price(" << price << ")\n";
	}

	return 0;
}
#endif

#ifdef BATCH11
#include <iostream>
#include <string>


template <typename T>
class MyVector
{
private:
	T* Data;      // 동적 배열 포인터
	int Size;     // 현재 데이터 개수
	int Capacity; // 현재 최대 수용량

public:
	// [문제 1] 생성자 (3점)
	// 초기 용량(InCapacity)만큼 메모리를 할당하고 변수들을 초기화하세요.
	MyVector(int InCapacity = 2)
	{
		// 로직 작성
		Data = new T[InCapacity];
		Capacity = InCapacity;
		Size = 0;
	}

	~MyVector()
	{
		if (Data) delete[] Data;
	}

	// [문제 2] Add 함수 (12점)
	// 1. 만약 배열이 가득 찼다면(Size == Capacity), 용량을 2배로 늘려야 합니다.
	// 2. 새로운 메모리를 할당하고 기존 데이터를 안전하게 이사시킨 뒤, 이전 메모리를 해제하세요.
	// 3. 마지막에 새로운 데이터를 추가하세요.
	void Add(const T& InData)
	{
		// 로직 작성 (메모리 재할당 프로세스 포함)
		if (Size == Capacity)
		{	//	full
			Reserve(Capacity * 2);
		}
		Data[Size] = InData;
		Size++;
	}

	void Reserve(int newCapacity)
	{	//	일단 작아지는 경우는 제외
		if (Capacity > newCapacity)	return;
		T* temp = new T[newCapacity];
		for (int i = 0; i < Capacity; i++)
		{
			temp[i] = Data[i];
		}
		delete Data;
		Data = temp;
		Capacity = newCapacity;
	}

	// [문제 3] operator[] 오버로딩 (5점)
	// 인덱스를 통해 데이터를 참조형으로 반환하세요.
	T& operator[](int Index)
	{
		// 로직 작성
		return Data[Index];
	}

	int GetSize() const { return Size; }
	int GetCapacity() const { return Capacity; }
};

int main()
{
	// 테스트: 초기 용량은 2지만, 3개를 넣어서 재할당이 일어나는지 확인합니다.
	MyVector<int> Vec;
	Vec.Add(10);
	Vec.Add(20);

	std::cout << "Before Resize - Size: " << Vec.GetSize() << ", Capacity: " << Vec.GetCapacity() << std::endl;

	Vec.Add(30); // 여기서 재할당 로직이 실행되어야 함

	std::cout << "After Resize - Size: " << Vec.GetSize() << ", Capacity: " << Vec.GetCapacity() << std::endl;
	std::cout << "Data: " << Vec[0] << ", " << Vec[1] << ", " << Vec[2] << std::endl;

	return 0;
}
#endif