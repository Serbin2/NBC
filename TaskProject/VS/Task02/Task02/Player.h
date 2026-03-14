#pragma once

#include <string>
#include <iostream>

class CMonster;
using namespace std;

class IPlayer
{
public:		//	누구나 접근 가능
	IPlayer();
	IPlayer(string name);
	virtual ~IPlayer() {};

	virtual void Attack() = 0;					//	순수 가상 함수
	virtual void Attack(CMonster* pMonster);	//	가상 함수
	void PrintPlayerStatus();
	void PrintRemainHP();

	string GetClassName() { return m_sClassName; };
	string GetUserName() { return m_sUserName; };

	int GetLevel() { return m_iLevel; };
	int GetHP() { return m_iHP; };
	int GetMP() { return m_iMP; };
	int GetATK() { return m_iATK; };
	int GetDEF() { return m_iDEF; };
	int GetINT() { return m_iINT; };
	int GetSPD() { return m_iSPD; };

	void SetUserName(string name) { m_sUserName = name; };
	void SetLevel(int lv) { m_iLevel = lv; };
	void SetHP(int hp) { m_iHP = hp; };
	void SetMP(int mp) { m_iMP = mp; };
	void SetATK(int atk) { m_iATK = atk; };
	void SetDEF(int def) { m_iDEF = def; };
	void SetINT(int intel) { m_iDEF = intel; };
	void SetSPD(int spd) { m_iDEF = spd; };


private:	//	자손도 접근 불가


protected:	//	자손은 접근 가능

	string m_sClassName;
	string m_sUserName;
	int m_iLevel;
	int m_iHP;
	int m_iMP;
	int m_iATK;
	int m_iDEF;
	int m_iINT;
	int m_iSPD;
};

