#pragma once

#include "Player.h"

class CMagician : public IPlayer
{
public:

	CMagician(string name);
	virtual ~CMagician() {};

	void Attack() override;
	void Attack(CMonster* pMonster) override;

private:


};