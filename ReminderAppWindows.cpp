// ReminderAppWindows.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ReminderAppWindows.h"
#include "combaseapi.h"
#define MAX_LOADSTRING 100
#define SUBMIT_DATE 198
#include <iostream>

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"The High Performance Gaming Reminder App";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND button;
HWND buttonOwner;
HWND description;

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

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
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
    HWND hWnd = CreateWindowW(szWindowClass, L"reminder app :^                    )", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    buttonOwner = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"ListBox",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Submit",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
       150,         // x position 
       50,         // y position 
       100,        //  width
       100,        // height
       hWnd,     // Parent window
       NULL,       // No menu.
       NULL,
       NULL);
   if (!buttonOwner) 
   {
       MessageBox(NULL, L"buttonOwner is nullptr", NULL, MB_OK);
       return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

  // description = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
    //   WS_CHILD | WS_VISIBLE, 100, 20, 140,
      // 20, hWnd, NULL, NULL, NULL);
   
   description = CreateWindowEx(
       WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
       L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
       L"Enter here",      // Button text 
       WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
       50,         // x position 
       50,         // y position 
       100,        //  width
       100,        // height
       hWnd,     // Parent window
       NULL,       // No menu.
       NULL,
       NULL);
       
   if (description) {
       MessageBox(NULL, L"description created", NULL, MB_OK);
   }
   else {
       MessageBox(NULL, L"error: description is nullptr", NULL, MB_OK);
   }

   button = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"OK",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       0,         // x position 
       0,         // y position 
       100,        // Button width
       100,        // Button height
       hWnd,     // Parent window
       (HMENU) SUBMIT_DATE,       // menu
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   if (button) {
       MessageBox(NULL, L"button created", NULL, MB_OK);
   }
   else {
       MessageBox(NULL, L"error: button is nullptr", NULL, MB_OK);
   }

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
