#include "PlayerMgr.h"
#include "MainMgr.h"

CPlayerMgr::CPlayerMgr()
{
	m_pMainMgr = NULL;
	m_bIsDelayRemove = false;
	m_PlayerMap.clear();
}

CPlayerMgr::~CPlayerMgr()
{
	for (auto it = m_PlayerMap.begin();it != m_PlayerMap.end();it++)
	{
		SAFE_DELETE(it->second);
	}

	m_PlayerMap.clear();
}

bool CPlayerMgr::Init(CMainMgr *pMainMgr)
{
	m_pMainMgr = pMainMgr;

	return true;
}

bool CPlayerMgr::IsExistPlayer(DWORD dwPlayerID)
{
	if (m_PlayerMap.find(dwPlayerID) != m_PlayerMap.end())
	{
		return true;
	}

	return false;
}

bool CPlayerMgr::IsExistPlayer(char* pPlayerAccountName)
{
	if (GetPlayerDataByAccountName(pPlayerAccountName))
		return true;

	return false;
}

//�������
int CPlayerMgr::AddPlayer(DWORD dwPlayerID, CPlayer *pPlayer)
{
	if (!IsExistPlayer(dwPlayerID))
	{
		Log("CPlayerMgr add player ID = %d", dwPlayerID);
		m_PlayerMap.insert(pair<DWORD, CPlayer*>(dwPlayerID, pPlayer));
		return 0;
	}
	return 1;
}

//�������
int CPlayerMgr::AddPlayer(CPlayer *pPlayer)
{
	return AddPlayer(pPlayer->GetPlayerID(), pPlayer);
}

//ɾ�����
void CPlayerMgr::RemovePlayer(DWORD dwPlayerID)
{
	if (IsExistPlayer(dwPlayerID))
	{
		Log("CPlayerMgr remove player ID = %d",dwPlayerID);
		CPlayer *pPlayer = (CPlayer *)m_PlayerMap[dwPlayerID];
		m_PlayerMap.erase(dwPlayerID);
		SAFE_DELETE(pPlayer);
	}
}

//ɾ�����
void CPlayerMgr::RemovePlayer(CPlayer *pPlayer)
{
	RemovePlayer(pPlayer->GetPlayerID());
}

//ɾ����� //����� Ч�ʵ� ���Ż� whb
void CPlayerMgr::RemovePlayer(ULLONG llConnectID)
{
	CPlayer *pPlayer = GetPlayerDataByConnectID(llConnectID);
	if (pPlayer)
	{
		if (pPlayer->GetPlayerConnectID() == llConnectID)
		{
			if (m_bIsDelayRemove)
			{
				pPlayer->SetIsWillRemove(true);
				pPlayer->SetCutTime(time(0));
			}
			else
			{
				RemovePlayer(pPlayer->GetPlayerID());
			}
		}
	}
}

//��ȡ�������
CPlayer* CPlayerMgr::GetPlayerDataByPlayerID(DWORD dwPlayerID)
{
	if (IsExistPlayer(dwPlayerID))
	{
		return m_PlayerMap[dwPlayerID];
	}

	return NULL;
}

//��ȡ�������
CPlayer* CPlayerMgr::GetPlayerDataByConnectID(ULLONG llConnectID)
{
	if (0 == llConnectID)
		return NULL;

	for (auto it = m_PlayerMap.begin(); it != m_PlayerMap.end(); it++)
	{
		CPlayer *pPlayer = it->second;
		if (pPlayer)
		{
			if (pPlayer->GetPlayerConnectID() == llConnectID)
			{
				return pPlayer;
			}
		}
	}

	return NULL;
}

CPlayer* CPlayerMgr::GetPlayerDataByAccountName(char* pPlayerAccountName)
{
	if (NULL == pPlayerAccountName || strncmp(pPlayerAccountName, "", 1) == 0)
		return NULL;

	for (auto it = m_PlayerMap.begin(); it != m_PlayerMap.end(); it++)
	{
		CPlayer *pPlayer = it->second;
		if (pPlayer)
		{
			if (strncmp(pPlayerAccountName, pPlayer->GetPlayerAccountName(), pPlayer->GetAccountNameLen()) == 0)
			{
				return pPlayer;
			}
		}
	}

	return NULL;
}

void CPlayerMgr::CleanPlayerData()
{
	time_t tTime = time(0);
	for (auto it = m_PlayerMap.begin(); it != m_PlayerMap.end();)
	{
		CPlayer *pPlayer = it->second;
		if (pPlayer)
		{
			if (pPlayer->GetIsWillRemove() && tTime >= pPlayer->GetCutTime() + TIMER_DELAY_REMOVE_PLAYER_TIME)
			{
				m_PlayerMap.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}
}