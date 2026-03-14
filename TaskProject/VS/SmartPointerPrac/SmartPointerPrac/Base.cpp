#include "Base.h"
#include <assert.h>

CBase::CBase()
{
	m_iRefCount++;
}

CBase::~CBase()
{
#ifdef _DEBUG
	if (m_iRefCount)
	{
		assert(0);
	}
#endif
}

CBase* CBase::GetReference()
{	
	m_iRefCount++;
	return this;
}

void CBase::Release()
{
	if (--m_iRefCount == 0)
	{
		delete this;
	}
}