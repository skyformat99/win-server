#ifndef __IDATABASE_H__
#define __IDATABASE_H__
//#include <afxmt.h>
#include <icrsint.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include<memory>
using namespace std;
#import "C:\Program Files\Common Files\System\ado\MSADO15.DLL" rename_namespace("ADOSE") rename("EOF","EndOfFile")
using namespace ADOSE;

typedef _com_error						CComError;						//COM ����
typedef _variant_t						CDBVarValue;					//���ݿ���ֵ


//����ȼ�
enum enTraceLevel
{
	TraceLevel_Info					=0,									//��Ϣ��Ϣ
	TraceLevel_Normal				=1,									//��ͨ��Ϣ
	TraceLevel_Warning				=2,									//������Ϣ
	TraceLevel_Exception			=3,									//�쳣��Ϣ
	TraceLevel_Debug				=4,									//������Ϣ
};

//SQL �쳣����
enum enSQLException
{
	SQLException_None				=0,									//û���쳣
	SQLException_Connect			=1,									//���Ӵ���
	SQLException_Syntax				=2,									//�﷨����
};

class IDataBase
{
	//���ӽӿ�
public:
	//������
	virtual VOID __cdecl OpenConnection()=NULL;
	//�ر�����
	virtual VOID __cdecl CloseConnection()=NULL;
	//������Ϣ
	virtual bool __cdecl SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)=NULL;
	//������Ϣ
	virtual bool __cdecl SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)=NULL;

	//�����ӿ�
public:
	//�������
	virtual VOID __cdecl ClearParameters()=NULL;
	//��ȡ����
	virtual VOID __cdecl GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue)=NULL;
	//�������
	virtual VOID __cdecl AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue)=NULL;

	//���ƽӿ�
public:
	//�л���¼
	virtual VOID __cdecl NextRecordset()=NULL;
	//�رռ�¼
	virtual VOID __cdecl CloseRecordset()=NULL;
	//�󶨶���
	virtual VOID __cdecl BindToRecordset(CADORecordBinding * pBind)=NULL;

	//��¼�ӿ�
public:
	//�����ƶ�
	virtual VOID __cdecl MoveToNext()=NULL;
	//�Ƶ���ͷ
	virtual VOID __cdecl MoveToFirst()=NULL;
	//�Ƿ����
	virtual bool __cdecl IsRecordsetEnd()=NULL;
	//��ȡ��Ŀ
	virtual LONG __cdecl GetRecordCount()=NULL;
	//������ֵ
	virtual LONG __cdecl GetReturnValue()=NULL;
	//��ȡ����
	virtual VOID __cdecl GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue)=NULL;

	//���ƽӿ�
public:
	//�洢����
	virtual VOID __cdecl ExecuteProcess(LPCTSTR pszSPName, bool bRecordset)=NULL;
	//ִ�����
	virtual VOID __cdecl ExecuteSentence(LPCTSTR pszCommand, bool bRecordset)=NULL;
};

//���ݿ��쳣
class IDataBaseException
{
public:
	//�쳣����
	virtual HRESULT __cdecl GetExceptionResult()=NULL;
	//�쳣����
	virtual LPCTSTR __cdecl GetExceptionDescribe()=NULL;
	//�쳣����
	virtual enSQLException __cdecl GetExceptionType()=NULL;
};

#endif