#include  "lock.h"

#ifdef _MSC_VER
CLock::CLock()
{
	//InitializeCriticalSection(&cs_);
	//��ת 2048��(��˵4000�ȽϺ�)��������ٽ�������ת�����ڼ��Ϊ���ã��õ����߳̾ͱ����˵ȴ���������
	//��ת���������ڶദ������������ṩ�������ܣ���ԭ��������һ��ѭ������תͨ��Ҫ���ڽ����ں�ģʽ�ȴ�״̬��
	InitializeCriticalSectionAndSpinCount(&cs_, 4000);
}
CLock::~CLock()
{ 
	DeleteCriticalSection(&cs_); 
}

//����
void CLock::Lock()
{ 
	EnterCriticalSection(&cs_); 
}                         

//������
bool CLock::TryLock()                                                    
{
	if (TryEnterCriticalSection(&cs_) == 0)
		return false;
	else
		return true;
}

void CLock::UnLock()
{ 
	LeaveCriticalSection(&cs_);
}
#else
CLock::CLock()
{
}
CLock::~CLock()
{
}

//����
void CLock::Lock()
{
}

//������
bool CLock::TryLock()
{
    return true;
}

void CLock::UnLock()
{
}
#endif

CLockMgr::CLockMgr(CLock* pLock, bool bAuto/*=true*/)
{
	nLockCount_ = 0;
	pLock_ = pLock;
	if(bAuto)  Lock();
}

CLockMgr::~CLockMgr()
{
	if (pLock_)
	{
		while(nLockCount_>0)
		    UnLock();
		pLock_ = NULL;
	}
}

void CLockMgr::Lock()
{
	if (pLock_)
	{
		pLock_->Lock();
		nLockCount_++;
	}
}

void CLockMgr::UnLock()
{
	if (pLock_)
	{
		nLockCount_--;
		pLock_->UnLock();
	}
}                                                 