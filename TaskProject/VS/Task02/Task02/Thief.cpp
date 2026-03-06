#include "Thief.h"
#include "Monster.h"

CThief::CThief(string name)
{
	m_sClassName = "Thief";
	m_sUserName = name;
}

void CThief::Attack()
{
	cout << "단검으로 빠르게 찌릅니다!" << endl;
}

void CThief::Attack(CMonster* pMonster)
{
    if (pMonster == nullptr)
    {
        return;
    }

    cout << "단검으로 적을 기습합니다!" << endl;

    int enemyDef = pMonster->GetDEF();
    int enemyHP = pMonster->GetHP();

    int damage = (m_iATK - enemyDef)/5;
    if (damage < 1)
    {
        damage = 1;
    }

    enemyHP -= damage * 5;
    
    pMonster->SetHP(enemyHP);

    cout << damage << "(으)로 5회 공격하여 "<< damage * 5 << "의 피해를 입혔습니다!" << endl;

    pMonster->CheckDead();
}