#pragma once
#include <string>;
#include <vector>;

using namespace std;

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class CPotionRecipe
{
public:
	// 생성자: 재료 목록을 받아 초기화하도록 수정
	CPotionRecipe(const std::string& name, const std::vector<std::string>& ingredients);

	string GetName() const { return m_sPotionName; };
	vector<string> GetIngredients() const { return m_asIngredients; };
	bool HasIngredient(string name);
	bool HasKeyword(string key);

	bool RemoveStock();
	void AddStock(int qt);


protected:

	string m_sPotionName;
	vector<string> m_asIngredients;

	int m_iStock;
};