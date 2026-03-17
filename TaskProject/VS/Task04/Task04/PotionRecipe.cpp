#include "PotionRecipe.h"


CPotionRecipe::CPotionRecipe(const string& name, const vector<string>& ingredients):
	m_sPotionName		( name ),
	m_asIngredients		(ingredients ),
	m_iStock			( 3 )
{

}

bool CPotionRecipe::HasIngredient(string name)
{
	int size = m_asIngredients.size();
	for (int i = 0; i < size; i++)
	{
		if (m_asIngredients[i] == name)
		{
			return true;
		}
	}
	return false;
}

bool CPotionRecipe::HasKeyword(string key)
{
	size_t ret = m_sPotionName.find(key);
	if (ret != string::npos)
	{	//	찾았습니다.
		return true;
	}

	//	찾지 못했습니다.
	//	레시피에서도 찾아봅니다.
	if (HasIngredient(key))
	{	//	찾았습니다.
		return true;
	}

	return false;
}

bool CPotionRecipe::RemoveStock()
{	//	재고를 한개 줄입니다.
	//	재고가 없으면 안됩니다.
	if (m_iStock < 1)
	{	//	재고가 부족합니다.
		return false;
	}

	//	재고가 충분합니다
	//	재고를 하나 뺍니다
	m_iStock--;

	return true;
}

void CPotionRecipe::AddStock(int qt)
{	//	재고를 더합니다.
	m_iStock += qt;

	if (m_iStock > 3)
	{	//	재고는 최대 세개입니다
		m_iStock = 3;
	}
}