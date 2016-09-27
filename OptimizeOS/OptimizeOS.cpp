// OptimizeOS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

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

BOOL
SetRegedit()
{
	BOOL	bRet = FALSE;

	LONG	lResult = 0;
	HKEY	hKey = NULL;
	DWORD	dwData = 0;


	__try
	{
		lResult = RegOpenKeyEx(
			HKEY_LOCAL_MACHINE,
			_T("SYSTEM\\CurrentControlSet\\Control\\Terminal Server"),
			0,
			KEY_ALL_ACCESS,
			&hKey
		);
		if (ERROR_SUCCESS != lResult)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "RegOpenKeyEx failed. (%d)", lResult);
			__leave;
		}

		dwData = 0;
		lResult = RegSetValueEx(
			hKey,
			_T("fDenyTSConnections"),
			0,
			REG_DWORD,
			(BYTE *)&dwData,
			sizeof(DWORD)
		);
		if (ERROR_SUCCESS != lResult)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "RegSetValueEx failed. (%d)", lResult);
			__leave;
		}
	}
	__finally
	{
		if (hKey)
		{
			RegFlushKey(hKey);

			RegCloseKey(hKey);
			hKey = NULL;
		}
	}

	__try
	{
		lResult = RegOpenKeyEx(
			HKEY_CURRENT_USER,
			_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),
			0,
			KEY_ALL_ACCESS,
			&hKey
		);
		if (ERROR_SUCCESS != lResult)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "RegOpenKeyEx failed. (%d)", lResult);
			__leave;
		}

		dwData = 0;
		lResult = RegSetValueEx(
			hKey,
			_T("HideFileExt"),
			0,
			REG_DWORD,
			(BYTE *)&dwData,
			sizeof(DWORD)
		);
		if (ERROR_SUCCESS != lResult)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "RegSetValueEx failed. (%d)", lResult);
			__leave;
		}
	}
	__finally
	{
		if (hKey)
		{
			RegFlushKey(hKey);

			RegCloseKey(hKey);
			hKey = NULL;
		}
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetServices();
	SetUac();
	SetRegedit();

	return 0;
}
