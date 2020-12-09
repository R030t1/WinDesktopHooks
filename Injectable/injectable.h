#pragma once

// Windows' handling of UTF-16 is broken and UTF-16 is a poor encoding. However,
// some Windows API functions are only available in the `wchar_t` type. _UNICODE
// and UNICODE will be defined to avoid passing `char *` strings to the WinAPI
// in an erroneous fashion. Compile with -municode when using MinGW-w64.
#define _UNICODE
#include <Windows.h>

BOOL WINAPI __declspec(dllexport) DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
);