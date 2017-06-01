#ifndef __PLAYER_MGR_H__
#define __PLAYER_MGR_H__
#include <unordered_map>
#include "Player.h"

using namespace std;

class CMainMgr;

class CPlayerMgr
{
public:
	CPlayerMgr();
	~CPlayerMgr();
private:
	CMainMgr    *m_pMainMgr;
	bool         m_bIsDelayRemove;  //�Ƿ��ӳ��Ƴ�

	//key=���ID��value=����� ָ��
	std::unordered_map<DWORD, CPlayer*> m_PlayerMap;
public:
	bool Init(CMainMgr *pMainMgr);
	inline DWORD  GetIsDelayRemove()const { return m_bIsDelayRemove; }
	inline void   SetIsDelayRemove(bool bIsDelayRemove) { m_bIsDelayRemove = bIsDelayRemove; }

	//����Ƿ����
	bool IsExistPlayer(DWORD dwPlayerID);
	bool IsExistPlayer(char* pPlayerAccountName);

	//�������
	int  AddPlayer(DWORD dwPlayerID, CPlayer *pPlayer);
	int  AddPlayer(CPlayer *pPlayer);

	//ɾ�����
	void RemovePlayer(DWORD dwPlayerID);
	void RemovePlayer(CPlayer *pPlayer);
	void RemovePlayer(ULLONG llConnectID);

	//��ȡ�������
	CPlayer* GetPlayerDataByPlayerID(DWORD dwPlayerID);
	CPlayer* GetPlayerDataByConnectID(ULLONG llConnectID);
	CPlayer* GetPlayerDataByAccountName(char* pPlayerAccountName);

	//��ɨ����
	void CleanPlayerData();
};

#endif // !__PLAYER_MGR_H__
