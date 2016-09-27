// OptimizeOS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	SetServices()
{
	BOOL bRet = FALSE;


	__try
	{
		// Windows Firewall/Internet Connection Sharing (ICS)
		CService::GetInstance()->Enable(_T("SharedAccess"));
		CService::GetInstance()->Start(_T("SharedAccess"));

		// Windows Firewall
		CService::GetInstance()->Enable(_T("MpsSvc"));
		CService::GetInstance()->Start(_T("MpsSvc"));

		// Windows Search
		CService::GetInstance()->Enable(_T("WSearch"));
		CService::GetInstance()->Start(_T("WSearch"));

		// Windows Time
		CService::GetInstance()->Enable(_T("W32Time"));
		CService::GetInstance()->Start(_T("W32Time"));

		// Windows Event Log
		CService::GetInstance()->Enable(_T("eventlog"));
		CService::GetInstance()->Start(_T("eventlog"));

		// System Event Notification
		CService::GetInstance()->Enable(_T("SENS"));
		CService::GetInstance()->Start(_T("SENS"));

		// Windows Update
		CService::GetInstance()->Enable(_T("wuauserv"));
		CService::GetInstance()->Stop(_T("wuauserv"));

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
