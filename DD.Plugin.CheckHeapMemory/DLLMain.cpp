#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	return true;
}

__declspec(dllexport) TCHAR* __cdecl PluginName(void)
{
	return L"CheckHeapMemory";
}
__declspec(dllexport) TCHAR* __cdecl PluginVersion(void)
{
	return L"0.1";
}

__declspec(dllexport) TCHAR* __cdecl PluginErrorMessage(void)
{
	return sErrorMessage;
}

__declspec(dllexport) DWORD __cdecl PluginDebugCheck(int iWinVer)
{
	HANDLE hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE,30,30);
	if(hHeap == INVALID_HANDLE_VALUE)
	{
		sErrorMessage = TEXT("HeapCreate: failed!");
		return -1;
	}

	TCHAR *pHeapBuffer = (TCHAR*)HeapAlloc(hHeap,NULL,30),
		*sTemp = (TCHAR*)malloc(4 * sizeof(TCHAR)),
		*sTempCat = (TCHAR*)malloc(16 * sizeof(TCHAR));
	if(pHeapBuffer == NULL || sTemp == NULL || sTempCat == NULL)
	{
		sErrorMessage = TEXT("HeapAlloc || malloc: failed to alloc memory");
		return -1;
	}

	bool bDebugged = false;
	int iHeapCount = 0,
		iHeapCatCount = 0;

	memset(sTempCat,0,16);
	while(!bDebugged && iHeapCount <= 30)
	{
		if(iHeapCatCount <= 4)
		{
			wsprintf(sTemp,L"%04X",*(pHeapBuffer + iHeapCount));
			if(wcsstr(sTemp,L"ABAB") != NULL || wcsstr(sTemp,L"FEEE") != NULL)
			{
				wcscat(sTempCat,sTemp);
				iHeapCatCount++;
			}
			iHeapCount++;
		}
		else
		{
			if(wcsstr(sTempCat,L"FEEEABABABABABABABAB") != NULL)
				bDebugged = true;
		}
	}

	HeapFree(hHeap,NULL,pHeapBuffer);
	HeapDestroy(hHeap);

	if(bDebugged)
		return 1;
	else
		return 0;
}