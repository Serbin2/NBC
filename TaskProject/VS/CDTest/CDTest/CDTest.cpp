#include <iostream>

using namespace std;

class ParentA
{
public:
	ParentA()
	{
		cout << "ParentA 클래스가 생성되었습니다" << endl;
	}

	virtual ~ParentA()
	{
		cout << "ParentA 클래스가 소멸되었습니다" << endl;
	}
};

class ParentB
{
public:
	ParentB()	{	cout << "ParentB 클래스가 생성되었습니다" << endl; }
	~ParentB()	{	cout << "ParnetB 클래스가 소멸되었습니다" << endl; }
};

class ChildA : public  ParentA
{
public:
	ChildA()
	{
		cout << "자식클래스 ChildA 클래스가 생성되었습니다" << endl;
	}

	ChildA(int i)
	{
		cout << "자식클래스 생성자의 오버로딩입니다 : "<< i << endl;
	}

	virtual ~ChildA()
	{
		cout << "자식클래스 ChildA 클래스가 소멸되었습니다" << endl;
	}
};

class ChildB : public ParentB
{
public:
	ChildB()
	{
		cout << "자식클래스 ChildB 클래스가 생성되었습니다" << endl;
	}

	~ChildB()
	{
		cout << "자식클래스 ChildB 클래스가 소멸되었습니다" << endl;
	}
};

int main()
{
	ParentA A;
	ChildA cc(1);

	cout << "ParentA 포인터에 ParentA 생성" << endl;
	ParentA* ppA = new ParentA();
	cout << endl << "ParentA 포인터에 ChildA 생성" << endl;
	ParentA* pcA = new ChildA();
	cout << endl << "ChildA 포인터에 ChildA 생성" << endl;
	ChildA* cA = new ChildA();
	cout << endl << "ChildA 클래스의 생성자 오버로딩 사용" << endl;
	ParentA* ppoA = new ChildA(1);
	//ChildA* cpA = new ParentA();	//	불가능하다

	cout << endl << "생성한 순서대로 삭제합니다" << endl;
	delete ppA;
	cout << endl;
	delete pcA;
	cout << endl;
	delete cA;
	cout << endl;
	delete ppoA;
	cout << endl;
	cout << endl << "소멸자에 virtual이 없다면 어떻게 될까?" << endl;
	ParentB* ppB = new ChildB();
	cout << endl;
	delete ppB;

	return 0;
}