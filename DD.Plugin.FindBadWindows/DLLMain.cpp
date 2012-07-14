#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"BadWindowsList";
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
	bool bDebugged = false;
	EnumWindows(EnumWindowsProc,(LPARAM)&bDebugged);
	if(bDebugged)
		return 1;
	else
		return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{
	vector<wstring> vWindowList;
	TCHAR* sTitel = (TCHAR*)malloc(255);
	bool* bDebugged = (bool*)lParam;

	vWindowList.push_back(L"Immunity Debugger");
	vWindowList.push_back(L"IDA Pro");
	vWindowList.push_back(L"Olly");
	vWindowList.push_back(L"- [CPU]");

	GetWindowText(hwnd,sTitel,255);

	for(int i = 0;i < vWindowList.size(); i++)
	{
		if(wcsstr(sTitel,vWindowList[i].c_str()))
			*bDebugged = true;
	}
	free(sTitel);
	return true;
}