#ifndef __GATEWAY_SERVERLOGIN_H__
#define __GATEWAY_SERVERLOGIN_H__
#include "GatewayServer.h"
#include "NetMsg.h"
class CGatewayServer;


/***********************************************************
*���ط������ֲ�ʽ����,�������¼������ͨ��
***********************************************************/

///*final (VS2013��֧��)*/class CGatewayServer : public CKernelMgr, virtual public CNoInherit < CGatewayServer > //��Ҫ�̳д���
class CGatewayServerLogin : public CKernelMgr
{
private:
	CGatewayServer   *m_pGatewayServer;

public:
	CGatewayServerLogin();
	~CGatewayServerLogin();
public:
	virtual void OnEvent(int timerID, void *data);
	virtual void OnCloseConnect(ULLONG llConnectID);
private:
	bool  OnLoginComplete(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);
public:
	bool  Init(DWORD dwMaxCount, DWORD dwListenPort);
	bool  Start();

	CGatewayServer* GetGatewayServerPtr();
	void SetGatewayServerPtr(CGatewayServer* pGatewayServer);

	//��Ϣ����
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);

	//�û�ע��
	bool  OnUserRegister(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);

	//�û���¼
	bool  OnUserLogin(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);

	//�û�����
	bool  OnUserEnter(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);
};


#endif