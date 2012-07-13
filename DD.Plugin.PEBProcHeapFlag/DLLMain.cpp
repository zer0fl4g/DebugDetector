#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"PEBProcHeapFlag";
}

__declspec(dllexport) TCHAR* __cdecl PluginVersion(void)
{
	return L"0.1";
}

__declspec(dllexport) TCHAR* __cdecl PluginErrorMessage(void)
{
	return sErrorMessage;
}

__declspec(dllexport) DWORD __cdecl PluginDebugCheck(void)
{
	if(GetWinVersion() == 3)
	{
		__asm
		{
			mov eax, fs:[18h]			;TEB
			mov eax, [eax + 30h]		;PEB
			mov eax, [eax + 18h]		;process heap
			cmp [eax + 44h],0			;heap force flags //seems changed on win7  xp = 10h
			jne DebuggerDetected
		}
	}
	else if (GetWinVersion() < 3)
	{
		__asm
		{
			mov eax, fs:[18h]			;TEB
			mov eax, [eax + 30h]	;PEB
			mov eax, [eax + 18h]	;process heap
			cmp [eax + 10h],0		;heap force flags //seems changed on win7  xp = 10h
			jne DebuggerDetected
		}
	}
	return 0;
	__asm{DebuggerDetected:}
	return 1;
}

int GetWinVersion()
{
	OSVERSIONINFO osVerInfo;
	OSVERSIONINFOEX osVerEx;

	ZeroMemory(&osVerInfo,sizeof(OSVERSIONINFO));
	ZeroMemory(&osVerEx,sizeof(OSVERSIONINFOEX));
	osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	osVerEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx(&osVerInfo);
	GetVersionEx((OSVERSIONINFO*)&osVerEx);

	if(osVerInfo.dwMajorVersion == 5 && osVerInfo.dwMinorVersion == 0 )
		return 0;//WIN_2000;

	if(osVerInfo.dwMajorVersion == 5 && osVerInfo.dwMinorVersion == 1 )
		return 1;//WIN_XP;

	if(osVerInfo.dwMajorVersion == 6 && osVerInfo.dwMinorVersion == 0 && osVerEx.wProductType == VER_NT_WORKSTATION )
		return 2;//WIN_VISTA;

	if(osVerInfo.dwMajorVersion == 6 && osVerInfo.dwMinorVersion == 1 && osVerEx.wProductType == VER_NT_WORKSTATION )
		return 3;//WIN_7;

	return -1;
}