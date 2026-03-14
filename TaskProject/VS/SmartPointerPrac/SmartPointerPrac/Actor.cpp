#include "Actor.h"
#include <iostream>

CActor::CActor()
{

}

CActor::~CActor()
{

}

CActor* CActor::Create()
{
	CActor* act = new CActor();

	if (!act->OnCreate())
	{
		act->Release();
		return nullptr;
	}

	return act;
}

bool CActor::OnCreate()
{
	std::cout << "내가 태어났다" << std::endl;
	return true;
}
