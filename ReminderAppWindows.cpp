// ReminderAppWindows.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ReminderAppWindows.h"
#include "combaseapi.h"
#include "InputScreen.h"
#include "CustomMacros.h"
#include <iostream>

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"The High Performance Gaming Reminder App";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//HWND baseWindow;
unique_ptr<InputScreen> inputScreen;
//InputScreen* inputScreen;
HWND button;
//HWND buttonOwner;
HWND dayText;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MessageBox(NULL,L"starting base window",NULL, MB_OK);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_REMINDERAPPWINDOWS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REMINDERAPPWINDOWS));

    MSG msg;

    //InputScreen inputScreen(szWindowClass, hInstance, nCmdShow);
    inputScreen = std::make_unique<InputScreen>(szWindowClass, hInstance, nCmdShow);

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    //delete inputScreen;
    
    CoUninitialize();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REMINDERAPPWINDOWS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REMINDERAPPWINDOWS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    /*
    baseWindow = CreateWindowW(szWindowClass, L"reminder app :^                    )", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!baseWindow)
    {
        return FALSE;
    }
    */

   //ShowWindow(baseWindow, nCmdShow);
   //UpdateWindow(baseWindow);

   
   //inputScreen = &inputScreen1;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case SUBMIT_DATE:
                MessageBox(NULL, L"button pressed", NULL, MB_OK);
                if (inputScreen) {
                    inputScreen->UploadInput();
                }
                if (dayText) {
                    WCHAR a[1000];
                    //LPSTR temp1;
                    LPWSTR temp = a;
                    GetWindowTextW(dayText, temp, 1000);
                    MessageBox(NULL, temp, NULL, MB_OK);
                    //MessageBox(NULL, L"button pressed", NULL, MB_OK);
                }
                
                break;
            case SET_PRESENT_DATE:
                if (inputScreen) {
                    inputScreen->UpdateCurrentTime();
                }
                break;
            case ONE_MONTH_CHECK:
                if (inputScreen) {
                    inputScreen->ToggleCheckBox(ONE_MONTH_CHECK);
                }
                break;
            case ONE_WEEK_CHECK:
                if (inputScreen) {
                    inputScreen->ToggleCheckBox(ONE_WEEK_CHECK);
                }
                break;
            case THREE_DAY_CHECK:
                if (inputScreen) {
                    inputScreen->ToggleCheckBox(THREE_DAY_CHECK);
                }
                break;
            case ONE_DAY_CHECK:
                if (inputScreen) {
                    inputScreen->ToggleCheckBox(ONE_DAY_CHECK);
                }
                break;
            case SIX_HOUR_CHECK:
                if (inputScreen) {
                    inputScreen->ToggleCheckBox(SIX_HOUR_CHECK);
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            // FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + -200));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
