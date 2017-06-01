#ifndef __KERNELMGR_H__
#define __KERNELMGR_H__
#include  <memory>
#include  "IKernelMgr.h"
#include  "TimerMgr.h"
#include  "NetError.h"

//index��roundindex�ĺ�������
#define   CONNECTID_MIX(index, RoundIndex)             ((ULLONG)(RoundIndex) << 32 | (ULLONG)(index))
#define   INDEX_SPLIT(llConnectID)                     (DWORD)((llConnectID) & 0xFFFFFFFF)
#define   ROUNDINDEX_SPLIT(llConnectID)                (DWORD)((llConnectID) >> 32)
#define   CONNECTID_MIXEX(pNetHead)                    CONNECTID_MIX(((CNetMsgHead*)(pNetHead))->reserve1_, ((CNetMsgHead*)(pNetHead))->reserve2_)
#define   RESERVE_SETCONNECTID(pNetHead, llConnectID)  ((CNetMsgHead*)(pNetHead))->reserve1_ = INDEX_SPLIT(llConnectID);((CNetMsgHead*)(pNetHead))->reserve2_ = ROUNDINDEX_SPLIT(llConnectID);


class CClientNetMgr;
class CQueueMsg;
class CLockFreeQueue;
class CTimerMgr;

class KERNEL_ENGINE_CLASS MKernelMgr :public IKernelMgr
{
protected:
	bool           bIsRunning_;            //�Ƿ��˳�
	CLockFreeMgr  *pQueueNormalMsg_;       //��ȡ����
	CTimerMgr     *pTimerMgr_;             //��ʱ������
	HANDLE         hEvent_;                //�ȴ��¼�
	     
public:
	MKernelMgr();
	virtual ~MKernelMgr();
private:
	virtual bool PrepareCloseConnect(ULLONG llConnectID){ return true; }
public:
	virtual bool Init(DWORD dwMaxCount, DWORD dwListenPort){ return true; }
	virtual bool Start(){ return true; }
	virtual CNetMgr* GetNetMgr(){ return NULL; }
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, DWORD dwRoundIndex){ return true; }
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, const void* pMsgData, DWORD dwMsgLen, DWORD dwRoundIndex){ return true; }
	virtual bool SendDataOld(DWORD dwIndex, const void* pAllMsgData, DWORD dwAllMsgLen, DWORD dwRoundIndex){ return true; }
	virtual bool SendData(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen){ return true; }
	virtual bool CloseConnect(ULLONG llConnectID){ return true; }
	virtual bool OnSocketRead(ULLONG llConnectID, const char* pData, DWORD dwSize){ return true; }
	virtual void OnCloseConnect(ULLONG llConnectID){ }
	virtual bool OnNormalMsgHandleOld(ULLONG llConnectID, NetMsgHead* pMsgHead, const void* pData){ return true; }
	virtual bool OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize){ return true; }
	virtual bool OnDBMsghandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType){ return true; }
public:
	virtual bool GetIsRunning();
	virtual CLockFreeMgr *GetNormalQueue();

	//timer ģ��
public:
	//��ʱ���߳�
	static unsigned int __stdcall TimerThread(void *pData);

	//��ʱ����Ӧ����,������WINDOWS��OnTimer
	//��AddEvent��func��=NULL��������func�������������Ϊdata
	virtual void OnEvent(int timerID, void *data);

	//���붨ʱ���¼�,������WINDOWS��SetTimer
	//timerID: ��ʱ��ID
	//seconds: ��ʱʱ��
	//fun:��ʱ�ص�����,��fun==NULL,����OnEvent����Ӧ
	//data:Я��������,������������5,��������"(int*)(5)"��������data,��������һ��ָ��,����Ҫ����Ա�Լ������ָ��,���,������ʱָ���ǲ��е�!!
	//type:ѭ����ʱ������ִֻ��һ�εĶ�ʱ��
	//timerID �� func����ͬʱΪ0����timerIDΪ0����Զ�����һ��ID
	//����ֵ��timerID���Զ������ID,����ֵ<=0��ʾ����¼�ʧ��.
	int AddEvent(int timerID, int interval, TimerCallBackFunc func = NULL, void *data = NULL, int type = CTimerMgr::CIRCLE);

	//�Ƴ���ʱ���¼�,������WINDOWS��KillTimer
	bool RemoveEvent(int timerID);

	//�Ƴ������¼�
	void RemoveAllEvent();

	//�Ƿ���ڶ�ʱ��ID
	virtual bool IsExistTimerID(int timerID);

	//ɾ���û�����
	virtual void DeleteTimerData(const void *data);

	//����ʱ���¼�
	virtual void HandleTimerEvent(IKernelMgr* pKernelMgr, void* pTimeData);

};

class KERNEL_ENGINE_CLASS CKernelMgr :public MKernelMgr
{
private:
	HANDLE         hNormalThreadHandle_;     //��ͨ�߳��¼�
	HANDLE         hBatchThreadHandle_;      //Ⱥ���߳��¼�
	HANDLE         hDBThreadHandle_;         //DB�߳��¼�
	HANDLE         hTimerThreadHandle_;      //��ʱ���߳��¼�

	HANDLE         hQueueNormalIOCP_;        //������ɶ˿�
	HANDLE         hQueueDBIOCP_;            //���ݿ�˿�
	HANDLE         hQueueTimerIOCP_;         //��ʱ���˿�

	CLockFreeMgr  *pQueueDBMsg_;             //���ݿ����
	
	CNetMgr       *pNetMgr_;                 //�������
	
	//������shared_ptr �� ���weak_ptr�� ������ ����ʵ���Ѿ��ͷţ��������̻߳������У��ҿ��ܷ���������Դʱ�ڴ���ʳ�������⡱ ��Ч�ʲ��ߣ����Ի��ǲ����¼��������
	//shared_ptr <CNetMgr>   pNetMgr_;         //������� 

public:
	CKernelMgr();
	virtual ~CKernelMgr();
public:
	virtual bool Init(DWORD dwMaxCount, DWORD dwListenPort);
	virtual bool Start();

public:
	virtual CNetMgr* GetNetMgr();
	//������Ϣ������������
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, DWORD dwRoundIndex);
	//������Ϣ���������ݼ����ݳ���
	virtual bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, const void* pMsgData, DWORD dwMsgLen, DWORD dwRoundIndex);
	//������Ϣ������������Ϣ����
	virtual bool SendDataOld(DWORD dwIndex, const void* pAllMsgData, DWORD dwAllMsgLen, DWORD dwRoundIndex);
	//������Ϣ������������Ϣ����
	virtual bool SendData(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen);

	//������Ϣ������������Ϣ����, ���ڷ�����뵥���ӿͻ���ͨ��
	bool SendData(CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen);

	//Ⱥ����Ϣ
	virtual bool SendBatchDataOld(DWORD dwMainID, DWORD dwSubID, const void* pMsgData, DWORD dwMsgLen/*, bool bAddQueue = 0*/);
	virtual bool SendBatchDataOld(const void* pMsgData, DWORD dwMsgLen/*, bool bAddQueue = 0*/);
	virtual bool SendBatchData(const void* pMsgData, DWORD dwMsgLen/*, bool bAddQueue = 0*/);
	virtual bool HandleDBData(ULLONG llConnectID, void* pData, DWORD dwSize, WORD wDBType);

private:
	//�ر�socket
	virtual bool  PrepareCloseConnect(ULLONG llConnectID);

public:
	//���ݶ�ȡ
	virtual bool OnSocketRead(ULLONG llConnectID, const char* pData, DWORD dwSize);
	//�ر�����
	virtual bool CloseConnect(ULLONG llConnectID);
	//�ͷ��������
	virtual void  OnCloseConnect(ULLONG llConnectID);
public:
	//�����߳�
	static unsigned int __stdcall QueueThread(void *pData);
	//���û���
	void  SetBuffLen(DWORD dwRecvLen, DWORD dwSendLen);
	DWORD GetMaxCount();
	void  SetIsSpecialClient(bool bIsSpecialClient);
	void  SetMsgConnectID(CNetMsgHead *pDestMsg, CNetMsgHead *pSourceMsg);
};


class KERNEL_ENGINE_CLASS CClientCKernelMgr:public MKernelMgr
{
public:
	CClientCKernelMgr();
	virtual ~CClientCKernelMgr();
private:
	CClientNetMgr*       pNetMgr_;               //�������
	HANDLE               hTimerThreadHandle_;    //��ʱ���߳̾��

public:
	virtual bool OnNetMessageOld(NetMsgHead *pNetMsgHead, char* pMsgData, DWORD dwMsgLen);
	virtual bool OnNetMessage(const void* pData, DWORD dwSize);
public:
	//��ʱ��������
	static void SendHeartBeatCallBack(void *data);
	//������ʱ
	static void ReConnectCallBack(void *data);
public:
	bool Init(LPCTSTR lpIP, USHORT usPort);
	bool Start();
	CClientNetMgr* GetNetMgrPtr();
	void CloseSocket();
public:
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID);                                        //������Ϣ������������
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID, const void* pMsgData, DWORD dwMsgLen);        //������Ϣ���������ݼ����ݳ���
	bool SendDataOld(const void* pAllMsgData, DWORD dwAllMsgLen);                                 //������Ϣ������������Ϣ����
	bool SendData(CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen);                             //������Ϣ������������Ϣ����
};

#endif