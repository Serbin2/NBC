#pragma once

class CBase
{
protected:
	//	流立 积己苞 流立 家戈阑 阜嚼聪促.
	CBase();
	virtual ~CBase();

public:	

	//static CBase* Create()	{	return new CBase();		}
	virtual bool OnCreate() = 0;
	void AddReference() { m_iRefCount++; };
	CBase* GetReference();

	void Release();

private:
	int m_iRefCount = 0;
};

