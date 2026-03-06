#pragma once

#include <string>

using namespace std;

class CItem
{
public :
	CItem();
	CItem(string name, int price) { m_sName = name; m_iPrice = price; };
	~CItem();

	bool operator>(const CItem& other) const;
	bool operator>=(const CItem& other) const;
	bool operator<(const CItem& other) const;
	bool operator<=(const CItem& other) const;

	void SetName(string name) { m_sName = name; };
	void SetPrice(int price) { m_iPrice; };

	string GetName() { return m_sName; };
	int GetPrice() { return m_iPrice; };

protected:
	string m_sName;
	int m_iPrice;

};