#include "Item.h"

CItem::CItem():
	m_sName		{ "NoName" },
	m_iPrice	{ 0 }
{

}

CItem::~CItem()
{

}

bool CItem::operator>(const CItem& other) const
{
	return this->m_iPrice > other.m_iPrice;
}

bool CItem::operator>=(const CItem& other) const
{
	return this->m_iPrice >= other.m_iPrice;
}

bool CItem::operator<(const CItem& other) const
{
	return this->m_iPrice < other.m_iPrice;
}

bool CItem::operator<=(const CItem& other) const
{
	return this->m_iPrice <= other.m_iPrice;
}