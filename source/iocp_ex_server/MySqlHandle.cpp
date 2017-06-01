#include "MySqlHandle.h"
#include "TimerID.h"
using namespace mysql;

CMySqlHandle::CMySqlHandle()
{
	m_pMainMgr = NULL;
}

CMySqlHandle::~CMySqlHandle()
{
	LogAll();
}

bool CMySqlHandle::Init(CMainMgr *pMainMgr)
{
	if (NULL == pMainMgr) return false;

	m_pMainMgr = pMainMgr;

	return true;
}

bool CMySqlHandle::OnMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType)
{
	switch (wDBType)
	{
	case db_player_login:
	{
		//�����¼
		BYTE  byResult = smd_login_success;
		DWORD dwPlayerID = share_rand()%1000+1;   //���ݿ��ѯ�õ���ֵ //whb ����

		//�жϽ��
		CPlayer *pPlayer = NULL;
		if (smd_login_success == byResult)//�ɹ�
		{
			pPlayer = new CPlayer;
			if (pPlayer)
			{
				pPlayer->SetPlayerID(dwPlayerID);
				pPlayer->SetPlayerConnectID(llConnectID);
			}
			else
			{
				byResult = smd_login_syserror;
			}
		}

		//���ؽ��
		m_pMainMgr->GetServerLogicHandlePtr()->OnLoginComplete(llConnectID, byResult, pPlayer);
	}break;
	case db_get_login_times:
	{
		
	}break;
	default:break;
	}

	return true;
}


//������Ҫ�κ��� OnMsgHandle ֱ�Ӵ������ݿ⴦�����Ϳ���
bool CMySqlHandle::OnDBHandleResult(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType)
{
	switch (wDBType)
	{
	case db_player_login:
	{
		
	}break;
	case db_get_login_times:
	{
		
	}break;
	default:break;
	}

	return true;
}

void CMySqlHandle::OnEvent(int timerID,const void *data)
{
	switch (timerID)
	{
	case timer_db_begin:
	{

	}break;
	default:
	{
		Log(LOG_DB, "invalid timerID=%d, file=%s,line=%d", timerID, __FILE__, __LINE__);
	}break;
	}
}

//ʵ��:
void CMySqlHandle::Example()
{
	return;

	//�ǵð�mysql��dll���ļ����� exeĿ¼/���̵���Ŀ¼(����ʱ) ��

	if (KeepAlive(0))
	{
		int nTemp = 29;
		char sql[256];
		QueryResult qr;

		//����-���
		Log(LOG_DB, "����/���� ���...\n");
		sprintf_s(sql, sizeof sql, "insert test_table (test) values(%d)", nTemp);
		sql[sizeof(sql) - 1] = 0;
		if (ExecuteSql(sql, strlen(sql), &qr) != 0 || qr.AffectedRows() != 1) //ExecuteStmtҲ����
		{
			Log(LOG_DB, "ExecuteSql insert fail.");
			return;
		}


		//��ѯ-���
		Log(LOG_DB, "��ѯ���...\n");
		sprintf_s(sql, sizeof sql, "select test,ID from test_table where ID = 1");
		sql[sizeof(sql) - 1] = 0;
		qr.Reset();
		if (ExecuteStmt(sql, strlen(sql), &qr) != 0)
		{
			Log(LOG_DB, "ExecuteSql select fail.");
			return;
		}
		if (0 == qr.AffectedRows()){ Log(LOG_DB, "Ӱ������Ϊ0.\n"); }
		else
		{
			long test_value, ID_value;
			QueryBind< 2 > bind;
			bind[0].BindLong(&test_value);
			bind[1].BindLong(&ID_value);

			//if (qr.FetchResult(bind) != 0)
			//	Log(LOG_DB,"FetchResult error:%s\n",mysql_stmt_error(m_pstmt));
			//else{

			//}			

			while (qr.FetchResult(bind) == 0)
			{
				Log(LOG_DB, "test_value=%d,ID_value=%d\n", test_value, ID_value);
			}
		}


		//#define CALL_POINT_LOG   "call p_pointlog (%d,  '%s',%d,%d,%d,%d,%d,%d)"  //Ҳ��������!!
		//��ѯ-�洢����
		Log(LOG_DB, "�洢����...\n");
		//�洢���̴�����ַ���Ϊsql��䣬���Բ����ǲ��ǻ�ִ�д�sql��䣿
		sprintf_s(sql, sizeof sql, "call test_getex(%d,'%s')",1000,"insert test_table (test) values(1000) ");  //sprintf_s(sql, sizeof sql, "call test_get");
		sql[sizeof(sql) - 1] = 0;
		qr.Reset();
		if (ExecuteStmt(sql, strlen(sql), &qr) != 0)
		{
			Log(LOG_DB, "ExecuteSql select fail.");
			return;
		}
		if (0 == qr.AffectedRows()){ Log(LOG_DB, "Ӱ������Ϊ0.\n"); }
		else
		{
			long test_value, ID_value;
			QueryBind< 2 > bind;
			bind[0].BindLong(&test_value);
			bind[1].BindLong(&ID_value);

			while (qr.FetchResult(bind) == 0)
			{
				Log(LOG_DB, "test_value=%d,ID_value=%d\n", test_value, ID_value);
			}
		}

	}
}

//-----------------------------------------------------
//ע����δ����ʵ�֣�����

//����ֿ�����
//#define UPDATE_WAREHOUSE            " update warehouse set locked = %d, databuf = ?, lastModify = now() where account = '%s' and serverid = %d "
//int CNetDBModuleEx::SaveWareHouseData(LPCSTR pAccount, DWORD dwServerID, bool blocked, SCommonData &pData)
//{
//	char sql[1024];
//	_snprintf(sql, sizeof sql, UPDATE_WAREHOUSE, blocked, pAccount, dwServerID);
//	sql[sizeof(sql) - 1] = 0;
//
//	// ����ѹ��
//	LPVOID pakBuf = tmpBuffer;
//	size_t pakSize = sizeof(tmpBuffer);
//	TryEncoding(&pData, COMMON_DATA, pakBuf, pakSize);
//
//	QueryResult qr;
//	QueryBind< 1 > args;
//	args[0].BindBlob(pakBuf, pakSize);
//	if (ExecuteStmt(sql, strlen(sql), &qr, args) != 0 || qr.AffectedRows() != 1)
//		return 0;
//
//	return 1;
//}






//#define UPDATE_PROPERTY_ONLYBUF     " update property set databuf = ?, rolebuf = ?, verify = ?, Level = ?, RankList = ?, tollgate = ?, viplv = ?, guideID = ?, savetime = now() where RoleID = '%d' " \
//                                    " and exists ( select 1 from warehouse where account = '%s' and serverid = %d ) "

//QueryBind<8> bind;
//bind[0].BindBlob(pakBuf, pakSize);
//bind[1].BindBlob(&snapshot, sizeof(snapshot));
//bind[2].BindULong(&verify);
//DWORD level = bdata.m_dwLevel;
//bind[3].BindULong(&level);
//
//NewRankList temp;
//
//memcpy(temp.name, bdata.m_Name, CONST_USERNAME);
//bind[4].BindBlob(&temp, sizeof(NewRankList));
//
//DWORD tollgate = 1111 /*bdata.m_dwLatestBattleFileID*/;//�ؿ�
//bind[5].BindULong(&tollgate);
//DWORD viplv = 0;//vip�ȼ�
//bind[6].BindULong(&viplv);
//DWORD guideID = 1111 /*bdata.m_NewbieGuideData.curGuide*/;//�������� ǧλΪ��������,����Ϊ��һ��
//bind[7].BindULong(&guideID);
//
//char sql[1024];
//_snprintf(sql, sizeof sql, UPDATE_PROPERTY_ONLYBUF, bdata.m_dwStaticID, pAccount, dwServerID);
//
//sql[sizeof(sql) - 1] = 0;
//
//QueryResult qr;
//if (ExecuteStmt(sql, strlen(sql), &qr, bind) != 0 || qr.AffectedRows() != 1)
//{
//	// ���⴦����δ���µ��κ�����ʱ��˵��������ݿ��ܴ��ڲ���Ӧ��serverid
//	if (qr.AffectedRows() == 0)
//		m_errmsg.ShowMsg(EDEBUG, "Save Player failure��[%s]", sql);
//	return 0;
//}
