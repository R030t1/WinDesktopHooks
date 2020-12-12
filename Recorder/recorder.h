#pragma once

#define _UNICODE

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <string>
#include <fstream>
#include <iostream>

#ifndef __kernel_entry
    #define __kernel_entry
#endif

#include <boost/program_options.hpp>
#include <boost/process.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <Windows.h>

int wmain(
    int argc, 
    wchar_t *argv[]
);

// The below provides a single command line. Command line parsing
// is nontrivial, using the above prototype causes MinGW and MSVC++
// to use provided functions.
/*
int APIENTRY wWinMain(
	_In_	 HINSTANCE	hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_	 LPWSTR		lpCmdLine,
	_In_ 	 int		nCmdShow
);
*/

LRESULT CALLBACK WndProc(
	_In_ HWND	hWnd,
	_In_ UINT	message,
	_In_ WPARAM	wParam,
	_In_ LPARAM	lParam
);