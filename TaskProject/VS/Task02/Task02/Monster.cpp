#include "Monster.h"

CMonster::CMonster():
	m_sName	("NoName"),
	m_iHP	( 50 ),
	m_iATK	( 30 ), 
	m_iDEF	( 10 ), 
	m_iSPD	( 10 )
{

}

CMonster::CMonster(string name) :
	m_sName	( name ),
	m_iHP	( 50 ),
	m_iATK	( 30 ),
	m_iDEF	( 10 ),
	m_iSPD	( 10 )
{

}

void CMonster::Attack(IPlayer* target)
{
	if (target == nullptr)
	{	//	no target
		return;
	}

	cout << m_sName << "의 공격!" << endl;

	int enemyDef = target->GetDEF();
	int enemyHP = target->GetHP();

	int damage = m_iATK - enemyDef;
	if (damage < 1)
	{
		damage = 1;
	}

	target->SetHP(enemyHP - damage);
	target->PrintRemainHP();
}

void CMonster::CheckDead()
{
	if (m_iHP < 0)
	{
		cout << m_sName <<"을 물리쳤습니다!" << endl;
	}
	else
	{
		cout << m_sName << "의 남은 체력 : " << m_iHP << endl;
	}	
}