#include "Magician.h"
#include "Monster.h"

CMagician::CMagician(string name)
{
	m_sClassName = "Magician";
	m_sUserName = name;
}

void CMagician::Attack()
{
	printf("마법 화살을 쏩니다!\n");
}

void CMagician::Attack(CMonster* pMonster)
{
    if (pMonster == nullptr)
    {
        return;
    }

    cout << "화염구를 발사해 적을 공격합니다!" << endl;

    int enemyDef = pMonster->GetDEF();
    int enemyHP = pMonster->GetHP();

    int damage = m_iINT - enemyDef;
    int burn = damage / 2;
    if (damage < 1)
    {
        damage = 1;
    }

    enemyHP -= damage;
    enemyHP -= burn;
    pMonster->SetHP(enemyHP);

    cout << damage << "의 피해를 입혔습니다!" << endl;
    cout << burn << "의 화상 피해를 입혔습니다!" << endl;

    pMonster->CheckDead();
}