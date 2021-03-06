#define _UNICODE
#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

HINSTANCE hInst;
WCHAR szTitle[] = L"Dummy";
WCHAR szMenuName[] = L"Dummy";
WCHAR szWindowClass[] = L"Dummy";

LRESULT CALLBACK WndProc(
	_In_ HWND	hWnd,
	_In_ UINT	message,
	_In_ WPARAM	wParam,
	_In_ LPARAM	lParam
);

int APIENTRY wWinMain(
	_In_	 HINSTANCE	hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_	 LPWSTR		lpCmdLine,
	_In_ 	 int		nCmdShow
) {	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEXW wcex = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = WndProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = LoadIconW(hInstance, IDI_APPLICATION),
        .hCursor = LoadCursorW(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        .lpszMenuName = szMenuName,
        .lpszClassName = szWindowClass,
        .hIconSm = LoadIconW(hInstance, IDI_APPLICATION),
    };
    if (!RegisterClassExW(&wcex)) {
        // TODO.
    }

    HWND hWnd = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );
    if (!hWnd) {
        // TODO.
    }

    ShowWindow(hWnd, SW_SHOWDEFAULT);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(
	_In_ HWND	hWnd,
	_In_ UINT	message,
	_In_ WPARAM	wParam,
	_In_ LPARAM	lParam
) {
    switch (message) {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}