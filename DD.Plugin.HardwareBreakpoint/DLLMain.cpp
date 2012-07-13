#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"Hardware Breakpoints";
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
	HANDLE hThread = GetCurrentThread();
	CONTEXT cTT; 
	bool bDebugged = false;

	ZeroMemory(&cTT,sizeof(CONTEXT));
	cTT.ContextFlags = CONTEXT_ALL;

	GetThreadContext(hThread,&cTT);

	if(cTT.Dr0 != NULL)
		bDebugged = true;
	if(cTT.Dr1 != NULL)
		bDebugged = true;
	if(cTT.Dr2 != NULL)
		bDebugged = true;
	if(cTT.Dr3 != NULL)
		bDebugged = true;

	if(bDebugged)
		return 1;
	else
		return 0;
}