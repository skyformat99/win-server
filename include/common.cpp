#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "define.h"
using namespace std;

#ifdef _MSC_VER
bool Unicode2Mulbytes(char* pDest, wchar_t *pSrc)
{
	if (pSrc == NULL || pDest == NULL)
		return false;

	int nDestLen = WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);
	if (0 == nDestLen)
		return false;
	WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pDest, nDestLen, NULL, NULL);

	return true;
}

bool Mulbytes2Unicode(wchar_t *pDest, char *pSrc)
{
	if (pSrc == NULL || pDest == NULL)
		return false;

	int nDestLen = MultiByteToWideChar(CP_ACP, 0, pSrc, -1, NULL, 0);
	if (0 == nDestLen)
		return false;
	MultiByteToWideChar(CP_ACP, 0, pSrc, -1, pDest, nDestLen);

	return true;
}


BOOL DirExist(const char *pszDirName)
{
	WIN32_FIND_DATA fileinfo;
	char _szDir[_MAX_PATH];
	strcpy_s(_szDir, pszDirName);
	int nLen = (int)strlen(_szDir);
	if ((_szDir[nLen - 1] == '\\') || (_szDir[nLen - 1] == '/'))
	{
		_szDir[nLen - 1] = '\0';
	}
	HANDLE hFind = ::FindFirstFile(_szDir, &fileinfo);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	if (fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		::FindClose(hFind);
		return true;
	}
	::FindClose(hFind);
	return false;
}

// ����Ŀ¼��������Ŀ¼�����Դ����༶��Ŀ¼
BOOL CreateDir(const char *pszDirName)
{
	BOOL bRet = false;
	char _szDir[_MAX_PATH];
	char _szTmp[_MAX_DIR];
	int nLen = 0;
	int idx;
	if ((DirExist(pszDirName)))
		return true;
	strcpy_s(_szDir, pszDirName);
	nLen = (int)strlen(_szDir);
	if (_szDir[nLen - 1] == '\\' || _szDir[nLen - 1] == '/')
	{
		_szDir[nLen - 1] = '\0';
	}
	nLen = (int)strlen(_szDir);
	memset(_szTmp, 0, _MAX_DIR);
	char _str[2];
	for (idx = 0; idx < nLen; idx++)
	{
		if (_szDir[idx] != '\\' && _szDir[idx] != '/')
		{
			_str[0] = _szDir[idx];
			_str[1] = 0;
			strcat_s(_szTmp, _str);
		}
		else
		{
			CreateDirectory(_szTmp, NULL);
			_str[0] = _szDir[idx];
			_str[1] = 0;
			strcat_s(_szTmp, _str);
		}

		if (idx == nLen - 1)
			CreateDirectory(_szTmp, NULL);
	}

	if (DirExist(_szTmp))
		return true;

	return false;
}
#else
#endif