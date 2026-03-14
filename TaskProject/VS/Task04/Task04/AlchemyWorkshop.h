#pragma once
#include <vector>
#include <iostream>
#include "PotionRecipe.h"

using namespace std;

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class CAlchemyWorkshop 
{
public:
	// addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
	void AddRecipe(const string& name, const vector<string>& ingredients);

	// 모든 레시피 출력 메서드
	void displayAllRecipes() const;

	CPotionRecipe* FindPotionByName(string name);
	//	이름의 일부로도 검색하는 함수
	//	여러개면 어떡함???
	bool FindPotionsByKeyword(string keyword, vector<CPotionRecipe>& outvec);

	bool FindPotionsByIngredient(string ingredient, vector<CPotionRecipe>& outvec);

private:
	std::vector<CPotionRecipe> m_aRecipes;

};