#pragma once

// Windows' handling of UTF-16 is broken and UTF-16 is a poor encoding. However,
// some Windows API functions are only available in the `wchar_t` type. _UNICODE
// and UNICODE will be defined to avoid passing `char *` strings to the WinAPI
// in an erroneous fashion. Compile with -municode when using MinGW-w64.
#define _UNICODE
#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <string>
#include <fstream>
#include <ios>
// TODO: Linking error on MSYS2 MinGW-w64.
#include <iostream>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

int APIENTRY wWinMain(
	_In_	 HINSTANCE	hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_	 LPWSTR		lpCmdLine,
	_In_ 	 int		nCmdShow
);

LRESULT CALLBACK WndProc(
	_In_ HWND	hWnd,
	_In_ UINT	message,
	_In_ WPARAM	wParam,
	_In_ LPARAM	lParam
);