#pragma once
#include <Windows.h>

extern "C"
{
	__declspec(dllexport) BOOL InstallHook(HWND hWnd);

	__declspec(dllexport) BOOL UninstallHook();
}

HINSTANCE g_hInstance;
HWND g_hWnd;

HHOOK g_hMouseHook;
HHOOK g_hKeyboardHook;

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
);

//鼠标钩子回调函数
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

//键盘钩子回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);