#include "Player.h"
#include "Monster.h"

IPlayer::IPlayer():
	m_sClassName    ( "NoClass" ),
    m_sUserName     ( "NoName" ),
    m_iLevel        ( 0 ),
    m_iHP           ( 50 ),
    m_iMP           ( 30 ),
	m_iATK          ( 30 ),
    m_iDEF          ( 15 ),
    m_iINT          ( 20 ),
    m_iSPD          ( 15 )
{

}

IPlayer::IPlayer(string name) :
	m_sClassName    ( "NoClass" ), 
    m_sUserName     ( name ), 
    m_iLevel        ( 0 ), 
    m_iHP           ( 50 ), 
    m_iMP           ( 30 ),
	m_iATK          ( 30 ), 
    m_iDEF          ( 15 ), 
    m_iINT          ( 20 ), 
    m_iSPD          ( 15 )
{

}


void IPlayer::PrintPlayerStatus()
{
    cout << "------------------------------------" << endl;
    cout << "* 현재 능력치" << endl;
    cout << "닉네임: " << m_sUserName;
    cout << "  직업: " << m_sClassName;
    cout << "  Lv. " << m_iLevel << endl;
    cout << "HP: " << m_iHP;
    cout << "  MP: " << m_iMP << endl;
    cout << "공격력: " << m_iATK;
    cout << "  방어력: " << m_iDEF;
    cout << "  지능: " << m_iINT;
    cout << "  속도: " << m_iSPD << endl;
    cout << "------------------------------------" << endl;
}

void IPlayer::Attack(CMonster* pMonster)
{
    if (pMonster == nullptr)
    {
        return;
    }

    this->Attack();

    int enemyDef = pMonster->GetDEF();
    int enemyHP = pMonster->GetHP();

    int damage = m_iATK - enemyDef;
    if (damage < 1)
    {
        damage = 1;
    }

    enemyHP -= damage;
    pMonster->SetHP(enemyHP);

    pMonster->CheckDead();
}

void IPlayer::PrintRemainHP()
{
    cout << "나의 남은 체력 : " << m_iHP << endl;
}