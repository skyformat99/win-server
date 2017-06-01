#ifndef __DISTRI_SERVER_HANDLE__H__
#define __DISTRI_SERVER_HANDLE__H__
#include "singleton.h"
#include "KernelMgr.h"

class CMainMgr;

//�ֲ�ʽ�����
class CDistriServerHandle:public CKernelMgr, virtual public CNoInherit < CDistriServerHandle >
{
public:
	CDistriServerHandle();
	~CDistriServerHandle();
private:
	CMainMgr   *m_pMainMgr;  //��������
public:
	//��ͨ��Ϣ����
	virtual bool OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);

	//���ݿ���Ϣ����
	virtual bool  OnDBMsghandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType);
	//��ʱ����Ϣ
	virtual void OnEvent(int timerID, void *data);

public:
	bool  Init(DWORD dwMaxCount, DWORD dwListenPort,CMainMgr* pMainMgr);
	bool  Start();

};

#endif