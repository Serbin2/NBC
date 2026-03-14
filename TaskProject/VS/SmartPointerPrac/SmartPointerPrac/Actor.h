#pragma once
#include "Base.h"


class CActor : public CBase
{
protected:
	//	사용자들은 생성자와 소멸자를 protected에 넣어야 함
	CActor();
	virtual ~CActor();

public:
	static CActor* Create();
	virtual bool OnCreate() override;

protected:
	//	멤버 변수들

};

