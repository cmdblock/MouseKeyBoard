#include "MouseKeyboard.h"

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		g_hInstance = hinstDLL;
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

BOOL InstallHook(HWND hMainWnd)
{
	g_hWnd = hMainWnd;
	g_hMouseHook = SetWindowsHookEx(WH_MOUSE, MouseProc, g_hInstance, 0);
	g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
	
	if (g_hWnd == FALSE)
	{
		MessageBox(NULL, L"窗口获取失败", L"主窗口", MB_OK);
		return FALSE;
	}
	else
	{
		WCHAR lpwStr[20];
		GetWindowText(g_hWnd, lpwStr, 20);
		//MessageBox(NULL, lpwStr, L"主窗口标题", MB_OK);
		return TRUE;
	}
}

BOOL UninstallHook()
{
	UnhookWindowsHookEx(g_hMouseHook);
	UnhookWindowsHookEx(g_hKeyboardHook);

	return TRUE;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
	}
	if (wParam == WM_MOUSEMOVE)
	{
		//PostMessage(g_hWnd, WM_USER, wParam, lParam);
		SendMessage(g_hWnd, WM_USER, wParam, lParam);
	}
	if (wParam == WM_LBUTTONDOWN)
	{
		//PostMessage(g_hWnd, WM_USER, wParam, lParam);
		SendMessage(g_hWnd, WM_USER + 1, wParam, lParam);
	}
	return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}