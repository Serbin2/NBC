#include "Archer.h"
#include "Monster.h"

CArcher::CArcher(string name)
{
	m_sClassName = "Archer";
	m_sUserName = name;
}

void CArcher::Attack()
{
	printf("활을 당겨 발사합니다!\n");
}

void CArcher::Attack(CMonster* pMonster)
{
    if (pMonster == nullptr)
    {
        return;
    }

    cout << "세개의 화살을 발사합니다!" << endl;

    int enemyDef = pMonster->GetDEF();
    int enemyHP = pMonster->GetHP();

    int damage = (m_iATK - enemyDef) / 3;
    if (damage < 1)
    {
        damage = 1;
    }

    enemyHP -= damage * 3;

    pMonster->SetHP(enemyHP);

    cout << damage << "(으)로 3회 공격하여 " << damage * 3 << "의 피해를 입혔습니다!" << endl;

    pMonster->CheckDead();
}