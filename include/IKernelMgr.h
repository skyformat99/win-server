#ifndef __IKERNELMGR__H__
#define __IKERNELMGR__H__
#include "define.h"

class CNetMgr;
class CLockFreeMgr;

class IKernelMgr
{
	friend CNetMgr;
public:
	virtual bool Init(DWORD dwMaxCount, DWORD dwListenPort) = 0;
	virtual bool Start() = 0;

public:
	virtual CNetMgr* GetNetMgr() = 0;
	virtual bool GetIsRunning() = 0;
	virtual CLockFreeMgr *GetNormalQueue() = 0;
	//������Ϣ������������
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, DWORD dwRoundIndex) = 0;
	//������Ϣ���������ݼ����ݳ���
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID,const void* pMsgData, DWORD dwMsgLen, DWORD dwRoundIndex) = 0;
	//������Ϣ������������Ϣ����
	virtual bool SendDataOld(DWORD dwIndex, const void* pAllMsgData, DWORD dwAllMsgLen, DWORD dwRoundIndex) = 0;
	//������Ϣ������������Ϣ����
	virtual bool SendData(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen) = 0;
	virtual bool CloseConnect(ULLONG llConnectID) = 0;
	virtual void OnEvent(int timerID, void *data) = 0;
	virtual bool RemoveEvent(int timerID) = 0;
	//�Ƿ���ڶ�ʱ��ID
	virtual bool IsExistTimerID(int timerID) = 0;
	//ɾ���û�����
	virtual void DeleteTimerData(const void *data) = 0;
	//����ʱ���¼�
	virtual void HandleTimerEvent(IKernelMgr* pKernelMgr, void* pTimeData) = 0;
private:
	//�ر�socket
	virtual bool  PrepareCloseConnect(ULLONG llConnectID) = 0;
public:
	//���ݶ�ȡ
	virtual bool  OnSocketRead(ULLONG llConnectID, const char* pData, DWORD dwSize) = 0;
	//�ͷ��������
	virtual void  OnCloseConnect(ULLONG llConnectID) = 0;
public:
	//��ͨ��Ϣ����
	virtual bool  OnNormalMsgHandleOld(ULLONG llConnectID, NetMsgHead* pMsgHead, const void* pData) = 0;
	virtual bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize) = 0;
	//���ݿ���Ϣ����
	virtual bool  OnDBMsghandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType) = 0;
};

#endif