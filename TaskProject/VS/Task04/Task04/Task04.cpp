#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "AlchemyWorkshop.h"
/*

1. * *초기 재고 설정 * *
-[]  자동 초기 재고 지급
- 새로운 레시피가 추가되면 해당 물약의 재고를 기본 3개로 설정하세요.

-- -

1. * *물약 찾기 및 지급 * *
-[]  물약 이름과 물약에 사용되는 재료 이름으로 창고를 검색하는 기능을 만드세요.
- 예) 물약 ‘간장계란밥’을 검색할 때, 이름인 ‘간장계란밥’을 입력해도, ‘간장’, ‘계란’, ’참기름’ 등 재료를 입력해도 검색이 되어야 합니다.
- []  재고가 1개 이상일 때만 모험가에게 줄 수 있고,
주면 재고가 1 감소합니다.

-- -

1. * *공병 반환하기 * *
-[]  모험가에게 물약을 다시 돌려받는 기능을 만드세요.
- []  돌려받으면 재고가 1 증가합니다.

-- -

1. * *창고 최대치(MAX) 제한 * *
-[]  반환받을 때 이미 3개라면, 더 이상 늘어나지 않도록 예외 처리를 해주세요.
- 모든 물약의 최대 재고는 3개입니다.
*/
unordered_map<string, int> bottle;
CAlchemyWorkshop myWorkshop;

int main() {
	
	
	while (true) {
		std::cout << "연금술 공방 관리 시스템" << std::endl;
		std::cout << "1. 레시피 추가" << std::endl;
		std::cout << "2. 모든 레시피 출력" << std::endl;
		std::cout << "3. 이름으로 물약 찾기" << std::endl;
		std::cout << "4. 재료로 물약 찾기" << std::endl;
		std::cout << "5. 키워드로 물약 찾기" << std::endl;
		std::cout << "6. 공병 돌려주기" << std::endl;
		std::cout << "7. 종료" << std::endl;
		std::cout << "선택: ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}

		if (choice == 1) {
			std::string name;
			std::cout << "물약 이름: ";
			std::cin.ignore(10000, '\n');
			std::getline(std::cin, name);

			//	이름 중복 처리
			CPotionRecipe* result = myWorkshop.FindPotionByName(name);
			if (result != nullptr)
			{	//	이미 있는 물약입니다.
				std::cout << "이미 존재하는 물약입니다." << std::endl;
				std::cin.clear();
				continue;
			}

			// 여러 재료를 입력받기 위한 로직
			std::vector<std::string> ingredients_input;
			std::string ingredient;
			std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

			while (true) 
			{
				std::cout << "재료 입력: ";
				std::getline(std::cin, ingredient);

				// 사용자가 '끝'을 입력하면 재료 입력 종료
				if (ingredient == "끝") 
				{
					break;
				}
				ingredients_input.push_back(ingredient);
			}

			// 입력받은 재료가 하나 이상 있을 때만 레시피 추가
			if (!ingredients_input.empty())
			{
				myWorkshop.AddRecipe(name, ingredients_input);
			}
			else {
				std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
			}

		}
		else if (choice == 2)
		{
			myWorkshop.displayAllRecipes();

		}
		else if (choice == 3)
		{
			std::string buf;
			std::cout << "이름을 입력하세요." << std::endl;
			std::cin >> buf;
			CPotionRecipe* result = myWorkshop.FindPotionByName(buf);
			if (result != nullptr)
			{	//	물약 목록을 찾았습니다.
				std::cout << "조건에 맞는 물약을 찾았습니다." << std::endl;
				std::cout << ">> " << result->GetName() << std::endl;
				if (result->RemoveStock())
				{	//	재고를 줄입니다
					std::cout << "물약을 한개 받았습니다." << std::endl;
					bottle[result->GetName()]++;
				}
				else
				{	//	재고가 없습니다.
					std::cout << "물약의 재고가 부족합니다." << std::endl;
				}
			}
			else
			{
				//	찾기 실패
				std::cout << "조건에 맞는 물약이 없습니다." << std::endl;
			}
			std::cin.clear();
		}
		else if (choice == 4)
		{
			std::string buf;
			std::cout << "재료를 입력하세요." << std::endl;
			std::cin >> buf;
			vector<CPotionRecipe> result;
			if (myWorkshop.FindPotionsByIngredient(buf, result))
			{	//	물약 목록을 찾았습니다.
				std::cout << "조건에 맞는 물약을 찾았습니다." << std::endl;
				int size = result.size();
				for (int i = 0; i < size; i++)
				{	
					std::cout << ">> " << result[i].GetName() << endl;
					if (result[i].RemoveStock())
					{	//	재고를 줄입니다
						std::cout << "물약을 한개 받았습니다." << std::endl;
						bottle[result[i].GetName()]++;
					}
					else
					{	//	재고가 없습니다.
						std::cout << "물약의 재고가 부족합니다." << std::endl;
					}
				}
			}
			else
			{
				//	찾기 실패
				std::cout << "조건에 맞는 물약이 없습니다." << std::endl;
			}
			std::cin.clear();
		}
		else if (choice == 5)
		{
			std::string buf;
			std::cout << "키워드를 입력하세요." << std::endl;
			std::cin >> buf;
			vector<CPotionRecipe> result;
			if (myWorkshop.FindPotionsByIngredient(buf, result))
			{	//	물약 목록을 찾았습니다.
				std::cout << "조건에 맞는 물약을 찾았습니다." << std::endl;
				int size = result.size();
				for (int i = 0; i < size; i++)
				{
					std::cout << ">> " << result[i].GetName() << endl;
					if (result[i].RemoveStock())
					{	//	재고를 줄입니다
						std::cout << "물약을 한개 받았습니다." << std::endl;
						bottle[result[i].GetName()]++;
					}
					else
					{	//	재고가 없습니다.
						std::cout << "물약의 재고가 부족합니다." << std::endl;
					}
				}
			}
			else
			{
				//	찾기 실패
				std::cout << "조건에 맞는 물약이 없습니다." << std::endl;
			}
			std::cin.clear();
		}
		else if (choice == 6)
		{	//	공병 돌려주기

		}
		else if (choice == 7) 
		{
			std::cout << "공방 문을 닫습니다..." << std::endl;
			break;
		}
		else 
		{
			std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
		}
	}

	return 0;
}


void ReturnBottle()
{
	bool stock = false;

	for (auto it : bottle)
	{
		if (it.second > 0)
		{

		}
	}
}