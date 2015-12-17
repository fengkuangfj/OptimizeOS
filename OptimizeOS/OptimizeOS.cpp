// OptimizeOS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	StopServices()
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

int _tmain(int argc, _TCHAR* argv[])
{
	StopServices();

	return 0;
}
