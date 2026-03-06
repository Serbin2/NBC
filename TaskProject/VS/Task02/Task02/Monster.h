#pragma once

#include "Player.h"

class CMonster
{
public:
	CMonster();
	CMonster(string name);
	~CMonster() {} ;

	void Attack(IPlayer* target);
	void CheckDead();

	string GetName() { return m_sName; };
	int GetHP() { return m_iHP; };
	int GetATK() { return m_iATK; };
	int GetDEF() { return m_iDEF; };
	int GetSPD() { return m_iSPD; };

	void SetName(string name) { m_sName = name; };
	void SetHP(int hp) { m_iHP = hp; };
	void SetATK(int atk) { m_iATK = atk; };
	void SetDEF(int def) { m_iDEF = def; };
	void SetSPD(int spd) { m_iSPD = spd; };

protected:

	string m_sName;
	int m_iHP;
	int m_iATK;
	int m_iDEF;
	int m_iSPD;

};
