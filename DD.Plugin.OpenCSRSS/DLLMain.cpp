#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"Open CSRSS Process";
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
	HANDLE hProcessSnap = NULL,hProc = NULL;
	PROCESSENTRY32W pe32w;
	bool bDebugged = false;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap != INVALID_HANDLE_VALUE)
	{
		pe32w.dwSize = sizeof(PROCESSENTRY32W);
		if(Process32First(hProcessSnap,&pe32w))
		{
			do
			{
				if(wcsstr(pe32w.szExeFile,L"csrss.exe") != NULL)
				{
					hProc = OpenProcess(PROCESS_ALL_ACCESS,false,pe32w.th32ProcessID);

					if(hProc != INVALID_HANDLE_VALUE)
					{
						bDebugged = true;
						CloseHandle(hProc);
					}
				}
			} while(Process32Next(hProcessSnap,&pe32w));
		}
		CloseHandle(hProcessSnap);
	}
	return bDebugged;
}