#pragma once

#include "Player.h"

class CWarrior : public IPlayer
{
public:

	CWarrior(string name);
	virtual ~CWarrior() {};

	void Attack() override;
	void Attack(CMonster* pMonster) override;

private:


};
