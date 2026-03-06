#pragma once

#include "Player.h"

class CThief : public IPlayer
{
public:

	CThief(string name);
	virtual ~CThief() {};

	void Attack() override;
	void Attack(CMonster* pMonster) override;

private:


};