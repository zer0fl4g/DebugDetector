#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"NtYieldExecution";
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
	int counter = 0x20;
	int debugged = 0;
	def_NtYieldExecution _NtYieldExecution = 0;
	HMODULE hModuleNtdll = GetModuleHandleW(TEXT("ntdll.dll"));
	if (!hModuleNtdll)
	{
		sErrorMessage = TEXT("ntdll handle not found");
		return 0;
	}
	_NtYieldExecution = (def_NtYieldExecution)GetProcAddress(hModuleNtdll, "NtYieldExecution");
	if (!_NtYieldExecution)
	{
		sErrorMessage = TEXT("NtYieldExecution not found");
		return 0;
	}
	do
	{
		Sleep(0xF);
		if (_NtYieldExecution() != _STATUS_NO_YIELD_PERFORMED)
		{
			debugged++;
		}
		counter--;
	} while (counter > 0);

	if (debugged <= 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}