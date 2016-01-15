// OptimizeOS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	SetServices()
{
	BOOL bRet = FALSE;


	__try
	{
		// Windows Search
		CService::GetInstance()->Stop(_T("WSearch"));
		CService::GetInstance()->Disable(_T("WSearch"));

		// Windows Update
		CService::GetInstance()->Stop(_T("wuauserv"));
		CService::GetInstance()->Disable(_T("wuauserv"));

		// Windows Firewall
		CService::GetInstance()->Stop(_T("MpsSvc"));
		CService::GetInstance()->Disable(_T("MpsSvc"));

		// Windows Firewall/Internet Connection Sharing (ICS)
// 		CService::GetInstance()->Stop(_T("SharedAccess"));
// 		CService::GetInstance()->Disable(_T("SharedAccess"));

		bRet = TRUE;
	}
	__finally
	{
		CService::ReleaseInstance();
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
