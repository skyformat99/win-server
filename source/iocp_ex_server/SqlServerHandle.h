#ifndef __CSQLSERVERHANDLE_H__
#define __CSQLSERVERHANDLE_H__
#include "MainMgr.h"
#include "../sqlserver/DataBaseAide.h"
class CMainMgr;

//sql server ��
class CSqlServerHandle
{
public:
	CSqlServerHandle();
	~CSqlServerHandle();
private:
	CMainMgr        *pMsgMgr_;
	CDataBaseAide    DBAide_;    //���ݿ�ӿ�
public:
	bool Init(CMainMgr *pMsgMgr);
	bool InitDB(CHAR * szDBAddress,WORD wDBPort,CHAR * szDBName,CHAR* szDBUser,CHAR* szDBPass);
	bool OnMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType);
	bool OnDBHandleResult(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType);
private:
	bool OnLoginTime(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType);
	bool OnLoginResult(ULLONG llConnectID, const void* pData, DWORD dwSize);
};

#endif