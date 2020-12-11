#include "recorder.h"
using namespace std;

HINSTANCE hInst;
WCHAR szTitle[] = L"Recorder";
WCHAR szMenuName[] = L"Recorder";
WCHAR szWindowClass[] = L"Recorder";

// TODO: Is any define more right? The below works with VSCode 
// autocomplete, and may be preferred by MSVC++.
#if defined(_WIN64)
WCHAR LibName[] = L"..\\Injectable\\libinjectable64.dll";
#elif defined(_WIN32)
WCHAR LibName[] = L"..\\Injectable\\libinjectable32.dll";
#endif
CHAR ProcName[] = "CallWndProc";

HHOOK GlobalCallWndProc;

int InitConsole()
{
    FILE *fConsole;

	if (!AllocConsole()) {
		return 1;
	}
	
	freopen_s(&fConsole, "CONOUT$", "w", stdout);
	freopen_s(&fConsole, "CONIN$", "r", stdin);
	//freopen_s(&fConsole, "CONERR$", "w", stderr);
	
	cout.clear();
	ios::sync_with_stdio();
    return 0;
}

int SetHooks(HWND hWnd) {
    HMODULE injectable = LoadLibraryW(LibName);
    if (NULL == injectable) {
        cout << "Failed to load library." << endl;
    }

    HOOKPROC CallWndProc = (HOOKPROC)GetProcAddress(injectable, ProcName);
    if (NULL == CallWndProc) {
        cout << "Failed to load hookproc." << endl;
        cout << GetLastError() << endl;
    }
    
    HWND h = FindWindow(NULL, L"Discord");
    if (NULL == h) {
        cout << "Failed to find window." << endl;
    }

    //DWORD tid = GetWindowThreadProcessId(h, NULL);
    DWORD tid = 0;
    GlobalCallWndProc = SetWindowsHookExW(WH_CALLWNDPROC, CallWndProc, injectable, tid);
    if (NULL == GlobalCallWndProc) {
        cout << "Failed to set hook." << endl;
    }

    return 0;
}

int UnsetHooks(HWND hWnd) {
    return UnhookWindowsHookEx(GlobalCallWndProc);
}

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
        InitConsole();
        SetHooks(hWnd);
        break;
    case WM_DESTROY:
        UnsetHooks(hWnd);
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}