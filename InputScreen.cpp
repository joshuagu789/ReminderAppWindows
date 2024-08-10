#include "InputScreen.h"
#include "combaseapi.h"
#include "WinUser.h"
#define MAX_LOADSTRING 100
#define SUBMIT_DATE 198
#include <iostream>

InputScreen::InputScreen(LPCWSTR lpClassName, HINSTANCE hInstance, int nCmdShow) {
	baseWindow = CreateWindowW(lpClassName, L"reminder app :^                    )", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!baseWindow)
    {
        MessageBox(NULL, L"warning: baseWindow is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    ShowWindow(baseWindow, nCmdShow);
    UpdateWindow(baseWindow);

    submitButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"OK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        150,         // x position 
        50,         // y position 
        100,        // Button width
        100,        // Button height
        baseWindow,     // Parent window
        (HMENU)SUBMIT_DATE,       // menu
        (HINSTANCE)GetWindowLongPtr(baseWindow, GWLP_HINSTANCE),
        NULL);

    if(!submitButton)
    {
        MessageBox(NULL, L"error: submitButton is nullptr for InputScreen", NULL, MB_OK);
        return;
    }
}