#ifndef __GATEWAY_SERVERLOGIC_H__
#define __GATEWAY_SERVERLOGIC_H__
#include "GatewayServer.h"
#include "NetMsg.h"
#include "ServerRegister.h"
class CGatewayServer;

/***********************************************************
*���ط������ֲ�ʽ����,�������߼�������ͨ��
***********************************************************/

///*final (VS2013��֧��)*/class CGatewayServer : public CKernelMgr, virtual public CNoInherit < CGatewayServer > //��Ҫ�̳д���
class CGatewayServerLogic : public CKernelMgr
{
private:
	CGatewayServer   *m_pGatewayServer;
	CServerRegister  *m_pServerRegister;
public:
	CGatewayServerLogic();
	~CGatewayServerLogic();

public:
	virtual void OnEvent(int timerID, void *data);
	virtual void OnCloseConnect(ULLONG llConnectID);

public:
	bool  Init(DWORD dwMaxCount, DWORD dwListenPort);
	bool  Start();

	CGatewayServer* GetGatewayServerPtr();
	void SetGatewayServerPtr(CGatewayServer* pGatewayServer);

	//��Ϣ����
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);

	bool SendDataByIndex(WORD wServerIndex, CNetMsgHead* pAllMsgData, DWORD dwAllMsgLen);
};

#endif