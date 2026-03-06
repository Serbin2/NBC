#include "Warrior.h"
#include "Monster.h"

CWarrior::CWarrior(string name)
{
	m_sClassName = "Warrior";
	m_sUserName = name;
}

void CWarrior::Attack()
{
	cout << "검을 휘두릅니다!" << endl;
}

void CWarrior::Attack(CMonster* pMonster)
{
    if (pMonster == nullptr)
    {
        return;
    }

    cout << "검을 휘둘러 적을 공격합니다!" << endl;

    int enemyDef = pMonster->GetDEF();
    int enemyHP = pMonster->GetHP();

    int damage = m_iATK - enemyDef;
    if (damage < 1)
    {
        damage = 1;
    }

    enemyHP -= damage;
    pMonster->SetHP(enemyHP);

    cout << damage << "의 피해를 입혔습니다!" << endl;

    pMonster->CheckDead();
}