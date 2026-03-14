#include "AlchemyWorkshop.h"

// addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
void CAlchemyWorkshop::AddRecipe(const string& name, const vector<string>& ingredients)
{
	//	이미 있는 물약이라면?

	m_aRecipes.push_back(CPotionRecipe(name, ingredients));
	std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
}


void CAlchemyWorkshop::displayAllRecipes() const
{
	if (m_aRecipes.empty()) {
		std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
		return;
	}

	std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
	for (size_t i = 0; i < m_aRecipes.size(); ++i)
	{
		std::cout << "- 물약 이름: " << m_aRecipes[i].GetName() << std::endl;
		std::cout << "  > 필요 재료: ";

		// 재료 목록을 순회하며 출력
		vector<string> ing = m_aRecipes[i].GetIngredients();
		for (size_t j = 0; j < ing.size(); ++j) {
			std::cout << ing[j];
			// 마지막 재료가 아니면 쉼표로 구분
			if (j < ing.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "---------------------------\n";
}

CPotionRecipe* CAlchemyWorkshop::FindPotionByName(string name)
{   //  이름으로 물약 찾기
	int size = m_aRecipes.size();
	
	for (int i = 0; i < size; i++)
	{
		if (m_aRecipes[i].GetName() == name)
		{
			return &m_aRecipes[i];
		}
	}

	return nullptr;
}

bool CAlchemyWorkshop::FindPotionsByKeyword(string keyword, vector<CPotionRecipe>& outvec)
{
	vector<CPotionRecipe> tempvec;
	bool retval = false;

	int size = m_aRecipes.size();
	for (int i = 0; i < size; i++)
	{	//	키워드로 찾기
		if (m_aRecipes[i].HasKeyword(keyword))
		{	//	가지고 있습니다.
			//	출력 배열에 추가합니다.
			tempvec.push_back(m_aRecipes[i]);
			retval = true;
		}
	}

	if(retval)	outvec = tempvec;

	return retval;
}

bool CAlchemyWorkshop::FindPotionsByIngredient(string ingredient, vector<CPotionRecipe>& outvec)
{   //  레시피에 해당 재료가 포함된 모든 물약을 찾습니다
	vector<CPotionRecipe> tempvec;
	bool retval = false;

	int size = m_aRecipes.size();
	for (int i = 0; i < size; i++)
	{
		if (m_aRecipes[i].HasIngredient(ingredient))
		{
			tempvec.push_back(m_aRecipes[i]);
			retval = true;
		}
	}

	if (retval)
	{
		outvec = tempvec;
	}
	return retval;
}