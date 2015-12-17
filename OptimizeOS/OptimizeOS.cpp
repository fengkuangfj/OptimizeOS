// OptimizeOS.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

BOOL
	SetServices()
{
	BOOL		bRet = FALSE;

	CService	Service;


	__try
	{
		// Windows Search
		Service.Stop(_T("WSearch"));
		Service.Disable(_T("WSearch"));

		// Windows Update
		Service.Stop(_T("wuauserv"));
		Service.Disable(_T("wuauserv"));

		// Windows Firewall
		Service.Stop(_T("MpsSvc"));
		Service.Disable(_T("MpsSvc"));

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	return bRet;
}

BOOL
	SetUac()
{
	BOOL bRet = FALSE;


	__try
	{
		CUac::Set(UAC_LEVEL_4);

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetServices();
	SetUac();

	_getch();

	return 0;
}
