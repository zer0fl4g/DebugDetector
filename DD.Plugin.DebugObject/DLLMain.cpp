#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"DebugObject";
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
	typedef NTSTATUS (WINAPI *pNtQueryInformationProcess)(HANDLE,UINT,PVOID,ULONG,PULONG); 

	HANDLE hDebugObject = NULL;
	NTSTATUS Status; 

	pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle(L"ntdll.dll"),"NtQueryInformationProcess"); 

	Status = NtQIP(GetCurrentProcess(),0x1e,&hDebugObject,4,NULL); 

	if (Status != 0x00000000)
		return 0;

	if(hDebugObject)
		return 1;
	else
		return 0;
}