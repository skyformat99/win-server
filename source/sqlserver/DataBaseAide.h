#ifndef DATABASE_AIDE_HEAD_FILE
#define DATABASE_AIDE_HEAD_FILE
#include "IDataBase.h"

#ifdef  _DB_EXPORT_
    #define DB_ENGINE_CLASS __declspec(dllexport)
#else
    #define DB_ENGINE_CLASS __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////

//���ݿ�����
class DB_ENGINE_CLASS CDataBaseAide
{
	//��������
protected:
	IDataBase *						m_pIDataBase;						//���ݶ���

	//��������
public:
	//���캯��
	CDataBaseAide(IDataBase * pIDataBase=NULL);
	//��������
	virtual ~CDataBaseAide();

	//������
public:
	//���ö���
	bool SetDataBase(IDataBase * pIDataBase);
	//��ȡ����
	IDataBase * GetDataBase();

	//��ȡ����
public:
	//��ȡ����
	INT GetValue_INT(LPCTSTR pszItem);
	//��ȡ����
	UINT GetValue_UINT(LPCTSTR pszItem);
	//��ȡ����
	LONG GetValue_LONG(LPCTSTR pszItem);
	//��ȡ����
	BYTE GetValue_BYTE(LPCTSTR pszItem);
	//��ȡ����
	WORD GetValue_WORD(LPCTSTR pszItem);
	//��ȡ����
	DWORD GetValue_DWORD(LPCTSTR pszItem);
	//��ȡ����
	FLOAT GetValue_FLOAT(LPCTSTR pszItem);
	//��ȡ����
	DOUBLE GetValue_DOUBLE(LPCTSTR pszItem);
	//��ȡ����
	LONGLONG GetValue_LONGLONG(LPCTSTR pszItem);
	//��ȡ����
	VOID GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//��ȡ����
	VOID GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime);
	//��ȡ����
	DATE GetValue_TimeStamp(LPCTSTR pszItem);
	//��ȡ�ַ�
	VOID GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount);
	//��ȡ�ַ�
	VOID GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount);

	//��������
public:
	//���ò���
	VOID ResetParameter();
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize);
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize);

	//�������
public:
	//�������
	VOID AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LPCSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);
	//�������
	VOID AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);

	//ִ�и���
public:
	//�洢����
	LONG ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
};

//////////////////////////////////////////////////////////////////////////

#endif