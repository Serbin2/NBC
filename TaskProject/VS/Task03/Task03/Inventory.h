#pragma once
#include <iostream>

using namespace std;

template<typename T> 
class TInventory
{
public:
	TInventory(int capacity = 10);
	~TInventory();

	TInventory(const TInventory<T>& other);
	void Assign(const TInventory<T>& other);

	bool AddItem(const T& item);
	bool RemoveLastItem();
	bool Resize(int newCapacity);
	void PrintAllItems() const;
	void SortItems();

	int GetSize() const { return m_iSize; };			//	현재 인벤토리에 들어있는 아이템의 수 입니다
	int GetCapacity() const { return m_iCapacity; };	//	현재 인벤토리의 최대 크기입니다

private:

	T* m_pArrItems;		//	인벤토리 동적 배열
	int m_iCapacity;	//	인벤토리의 최대 크기
	int m_iSize;		//	인벤토리에 저장된 아이템 수
};

#include <algorithm>

template<typename T>
TInventory<T>::TInventory(int capacity) :
	m_iSize(0)
{
	m_iCapacity = capacity;
	if (m_iCapacity < 1)
	{
		m_iCapacity = 1;
	}

	m_pArrItems = new T[m_iCapacity];
}

template<typename T>
TInventory<T>::~TInventory()
{
	delete[] m_pArrItems;
	m_pArrItems = nullptr;
}

template<typename T>
TInventory<T>::TInventory(const TInventory<T>& other)	//	other : 이미 생성되어있는 다른 객체
{
	this->m_iCapacity = other.m_iCapacity;
	this->m_iSize = other.m_iSize;
	this->m_pArrItems = new T[this->m_iCapacity];
	for (int i = 0; i < this->m_iSize; i++)
	{
		this->m_pArrItems[i] = other.m_pArrItems[i];
	}
	cout << "인벤토리 복사 완료" << endl;
}

template<typename T>
void TInventory<T>::Assign(const TInventory<T>& other)
{
	delete[] this->m_pArrItems;

	this->m_iCapacity = other.m_iCapacity;
	this->m_iSize = other.m_iSize;
	this->m_pArrItems = new T[this->m_iCapacity];
	for (int i = 0; i < this->m_iSize; i++)
	{
		this->m_pArrItems[i] = other.m_pArrItems[i];
	}
	cout << "인벤토리 복사 완료" << endl;
}

template<typename T>
bool TInventory<T>::AddItem(const T& item)
{	//	인벤토리에 아이템을 추가합니다.
	//	여유 공간이 있는지 확인하고 여유 공간이 있을 때에만 추가하도록 합니다
	//	아이템을 추가하면 사이즈를 증가시킵니다.
	//	공간이 부족하다면 경고문을 출력하도록 합니다.

	if (m_iSize >= m_iCapacity)
	{	//	여유 공간 부족
		/*
		cout << "인벤토리가 꽉 찼습니다!" << endl;
		return false;
		*///	경고문을 출력하지 않고 두배 크기로 재할당 합니다.	

		this->Resize(m_iCapacity * 2);
	}

	//	아이템을 채웁니다
	m_pArrItems[m_iSize] = item;
	m_iSize++;

	//	아이템을 성공적으로 채웠습니다.
	return true;
}

template<typename T>
bool TInventory<T>::RemoveLastItem()
{	//	인벤토리의 마지막 아이템을 제거합니다
	//	실제로 메모리를 지우는 것이 아닌 size만 조정하여 마지막 배열의 아이템에 접근하지 못하도록 합니다
	//	아이템이 존재하지 않는다면 경고문을 출력하도록 합니다.

	if (m_iSize <= 0)
	{	//	빈 찬합
		cout << "인벤토리가 비어있습니다." << endl;
		return false;
	}

	m_iSize--;

	return true;
}

template<typename T>
bool TInventory<T>::Resize(int newCapacity)
{	//	newCapacity만큼 최대 크기를 재할당합니다.
	if (m_iCapacity == newCapacity)
	{	//	같은 크기입니다
		//	작업이 불필요합니다.
		return true;
	}

	T* tmp = new T[newCapacity];	
	m_iCapacity = newCapacity;

	if (m_iSize > m_iCapacity)
	{
		m_iSize = m_iCapacity;
	}

	for (int i = 0; i < m_iSize; i++)
	{
		tmp[i] = m_pArrItems[i];
	}

	delete[] m_pArrItems;
	m_pArrItems = tmp;

	//cout << "resize" << endl;

	return true;
}

template<typename T>
void TInventory<T>::PrintAllItems() const
{	//	배열에 있는 아이템들의 정보를 출력합니다
	//	비어있다면 해당 안내를 출력합니다

	if (m_iSize <= 0)
	{	//	인벤토리가 비어있음.
		cout << "비어있음." << endl;
		return;
	}

	for (int i = 0; i < m_iSize; i++)
	{
		cout << "[이름 : " << m_pArrItems[i].GetName() << ", 가격 : " << m_pArrItems[i].GetPrice() << "G]" << endl;
	}

}

template<typename T>
void TInventory<T>::SortItems()
{
	if (m_iSize < 2)
	{	//	항목이 둘 이상 있어야 정렬의 의미가 있으므로
		return;
	}
	std::sort(m_pArrItems, m_pArrItems + m_iSize);
}