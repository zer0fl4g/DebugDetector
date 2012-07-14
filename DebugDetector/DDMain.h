#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <vector>
#include "resource.h"
#include <CommCtrl.h>

using namespace std;

struct srcPlugin 
{
	DWORD dwName;
	DWORD dwVersion;
	DWORD dwDebugCheck;
	DWORD dwErrorMessage;
	HMODULE hPlugin;
};

INT_PTR CALLBACK MainDLGProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

bool LoadPlugins();
bool ExecutePlugins();

typedef TCHAR* (*PluginVersion)(void);
typedef TCHAR* (*PluginName)(void);
typedef TCHAR* (*PluginErrorMessage)(void);
typedef DWORD  (*PluginDebugCheck)(void);


HWND hwDlgMainFrame = NULL;

int iDetectNum = 0;

vector<srcPlugin> vPluginList;