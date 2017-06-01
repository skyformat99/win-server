#ifndef DATA_BASE_ENGINE_HEAD_FILE
#define DATA_BASE_ENGINE_HEAD_FILE

#ifndef __DATABASE_H__
#define __DATABASE_H__
//#include <afxdisp.h>

//���ͷ�ļ�
#include "IDataBase.h"

//////////////////////////////////////////////////////////////////////////
typedef struct tagTime
{
	DATE time;
} tagTime;

//ADO ������
class CADOError : public IDataBaseException
{
	//��������
protected:
	enSQLException					m_enErrorType;						//�������
	string/*CString*/			                m_strErrorDescribe;					//������Ϣ

	//��������
public:
	//���캯��
	CADOError();
	//��������
	virtual ~CADOError();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID __cdecl Release()
	{
		return /*true*/;
	}
	//�Ƿ���Ч
	virtual bool __cdecl IsValid()
	{
		//return AfxIsValidAddress(this, sizeof(CADOError)) ? true : false;  //whb
		return IsBadWritePtr(this,sizeof(CADOError))?false:true;
	}
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���ܽӿ�
public:
	//��������
	virtual enSQLException __cdecl GetExceptionType()
	{
		return m_enErrorType;
	}
	//��������
	virtual LPCTSTR __cdecl GetExceptionDescribe()
	{
		return /*m_strErrorDescribe*/m_strErrorDescribe.c_str(); //whb
	}
	//�쳣����
	virtual HRESULT __cdecl GetExceptionResult()
	{
		return (HRESULT)0;    //
	}

	//���ܺ���
public:
	//���ô���
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//���ݿ����
class CDataBase : public IDataBase
{
	//��Ϣ����
protected:
	CADOError						m_ADOError;							//�������
	string/*CString*/				            m_strConnect;						//�����ַ���
	string/*CString*/   				        m_strErrorDescribe;					//������Ϣ

	//״̬����
protected:
	DWORD							m_dwConnectCount;					//���Դ���
	DWORD							m_dwConnectErrorTime;				//����ʱ��
	const DWORD						m_dwResumeConnectCount;				//�ָ�����
	const DWORD						m_dwResumeConnectTime;				//�ָ�ʱ��

	//�ں˱���
protected:
	_CommandPtr						m_DBCommand;						//�������
	_RecordsetPtr					m_DBRecordset;						//��¼������
	_ConnectionPtr					m_DBConnection;						//���ݿ����

	//��������
public:
	//���캯��
	CDataBase();
	//��������
	virtual ~CDataBase();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID __cdecl Release()
	{
		if (IsValid()) delete this;
		return /*true*/;
	}
	//�Ƿ���Ч
	virtual bool __cdecl IsValid()
	{
		//whb
		//return AfxIsValidAddress(this, sizeof(CDataBase)) ? true : false;
		return IsBadWritePtr(this,sizeof(CADOError))?false:true;
	}
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//������
	virtual VOID __cdecl OpenConnection();
	//�رռ�¼
	virtual VOID __cdecl CloseRecordset();
	//�ر�����
	virtual VOID __cdecl CloseConnection();
	//��������
	virtual bool __cdecl TryConnectAgain(bool bFocusConnect, CComError * pComError);
	//������Ϣ
	virtual bool __cdecl SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//������Ϣ
	virtual bool __cdecl SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//�л���¼
	virtual VOID __cdecl NextRecordset();

	//״̬�ӿ�
public:
	//�Ƿ����Ӵ���
	virtual bool __cdecl IsConnectError();
	//�Ƿ��
	virtual bool __cdecl IsRecordsetOpened();

	//��¼���ӿ�
public:
	//�����ƶ�
	virtual void __cdecl MoveToNext();
	//�Ƶ���ͷ
	virtual void __cdecl MoveToFirst();
	//�Ƿ����
	virtual bool __cdecl IsRecordsetEnd();
	//��ȡ��Ŀ
	virtual long __cdecl GetRecordCount();
	//��ȡ��С
	virtual long __cdecl GetActualSize(LPCTSTR pszParamName);
	//�󶨶���
	virtual VOID __cdecl BindToRecordset(CADORecordBinding * pBind);
	//��ȡ����
	virtual VOID __cdecl GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//�ֶνӿ�
public:
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, WORD & wValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, INT & nValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, LONG & lValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize);
	//��ȡ���� ȥ��MFC���� COleDateTime �滻�� tagTime,��û���ԣ���֪������ǲ�����ȷ...whb
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, tagTime & Time/*COleDateTime & Time*/);
	//��ȡ����
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, bool & bValue);

	//�������ӿ�
public:
	//�������
	virtual void __cdecl AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue);
	//ɾ������
	virtual void __cdecl ClearParameters();
	//��ò���
	virtual void __cdecl GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue);
	//��ȡ������ֵ
	virtual long __cdecl GetReturnValue();

	//ִ�нӿ�
public:
	//ִ�����
	virtual VOID __cdecl ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
	//ִ������
	virtual VOID __cdecl ExecuteSentence(LPCTSTR pszCommand, bool bRecordset);

	//�ڲ�����
private:
	//��ȡ����
	LPCTSTR GetComErrorDescribe(CComError & ComError);
	//���ô���
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//����ģ��
class IServiceModule
{
	//��������
	virtual bool __cdecl StartService()=NULL;
	//ֹͣ����
	virtual bool __cdecl ConcludeService()=NULL;
};

//���ݿ�����
class IDataBaseEngine : public IServiceModule
{
	//���ýӿ�
public:
	//����ģ��
	virtual bool __cdecl SetDataBaseEngineSink(IServiceModule * pIUnknownEx)=NULL;

	//�����¼�
public:
	//ʱ���¼�
	virtual bool __cdecl PostDataBaseTimer(DWORD dwTimerID, WPARAM dwBindParameter)=NULL;
	//�����¼�
	virtual bool __cdecl PostDataBaseControl(WORD wControlID, VOID * pData, WORD wDataSize)=NULL;
	//�����¼�
	virtual bool __cdecl PostDataBaseRequest(WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize)=NULL;
};

//���ݿ������
class CDataBaseEngine : public IDataBaseEngine
{
	//�ں˱���
protected:
	bool							m_bService;							//���б�־
	//CQueueServiceEvent				m_QueueServiceEvent;				//���ж���
	//IDataBaseEngineSink				* m_pIDataBaseEngineSink;			//֪ͨ����

	//��������
public:
	//���캯��
	CDataBaseEngine(void);
	//��������
	virtual ~CDataBaseEngine(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID __cdecl Release()
	{
		if (IsValid()) delete this;
		return /*true*/;
	}
	//�Ƿ���Ч
	virtual bool __cdecl IsValid()
	{
		//whb
		//return AfxIsValidAddress(this, sizeof(CDataBaseEngine)) ? true : false;
		return IsBadWritePtr(this,sizeof(CADOError))?false:true;
	}
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��������
	virtual bool __cdecl StartService();
	//ֹͣ����
	virtual bool __cdecl ConcludeService();

	//���ýӿ�
public:
	//����ģ��
	virtual bool __cdecl SetDataBaseEngineSink(IServiceModule * pIDataBase);

	//���нӿ�
public:
	//���нӿ�
	virtual void __cdecl OnQueueServiceSink(WORD wIdentifier, void * pBuffer, WORD wDataSize);

	//�����¼�
public:
	//ʱ���¼�
	virtual bool __cdecl PostDataBaseTimer(DWORD dwTimerID, WPARAM dwBindParameter);
	//�����¼�
	virtual bool __cdecl PostDataBaseControl(WORD wControlID, VOID * pData, WORD wDataSize);
	//�����¼�
	virtual bool __cdecl PostDataBaseRequest(WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////

#endif

#endif