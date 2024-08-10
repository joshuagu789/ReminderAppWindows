#include "InputScreen.h"
#include "combaseapi.h"
#include "WinUser.h"
#define MAX_LOADSTRING 100
#define SUBMIT_DATE 198
#include <iostream>
#include <chrono>
#include <format>
#include <ctime>
#include <string>
#include <thread>

void UpdateCurrentTime(HWND yearText, HWND monthText, HWND dayText, HWND hourText, HWND minuteText);    //forward declaration

InputScreen::InputScreen(LPCWSTR lpClassName, HINSTANCE hInstance, int nCmdShow) {

	baseWindow = CreateWindowW(lpClassName, L"The High Performance Gaming Reminder App", WS_OVERLAPPEDWINDOW,
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
        600,         // x position 
        100,         // y position 
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

    caption = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Year:              Month:              Day:                  Hour:               Minute:     ",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER | WS_CAPTION,  // Styles 
        100,         // x position 
        50,         // y position 
        600,        //  width
        50,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!caption)
    {
        MessageBox(NULL, L"error: caption is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    minuteText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Enter here",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        500,         // x position 
        100,         // y position 
        100,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if(!minuteText) 
    {
        MessageBox(NULL, L"error: minuteText is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    hourText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Enter here",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        400,         // x position 
        100,         // y position 
        100,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!hourText)
    {
        MessageBox(NULL, L"error: hourText is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    dayText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Enter here",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        300,         // x position 
        100,         // y position 
        100,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!dayText)
    {
        MessageBox(NULL, L"error: dayText is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    monthText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"Enter here",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        200,         // x position 
        100,         // y position 
        100,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!monthText)
    {
        MessageBox(NULL, L"error: monthText is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    yearText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"2024",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        100,         // x position 
        100,         // y position 
        100,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!yearText)
    {
        MessageBox(NULL, L"error: yearText is nullptr for InputScreen", NULL, MB_OK);
        return;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread updater(UpdateCurrentTime, yearText, monthText, dayText, hourText, minuteText);
    updater.join();
}

//void InputScreen::UpdateCurrentTime(HWnd) {
void UpdateCurrentTime(HWND yearText, HWND monthText, HWND dayText, HWND hourText, HWND minuteText) {

    //if (!InputScreenIsValid()) 
    //{
    //    MessageBox(NULL, L"error: invalid input screen on UpdateCurrentTime's call to InputScreenIsValid in InputScreen", NULL, MB_OK);
    //    return;
    //}

    if (!yearText || !monthText || !dayText || hourText || minuteText) {
        MessageBox(NULL, L"error: invalid input screen on UpdateCurrentTime's call to InputScreenIsValid in InputScreen", NULL, MB_OK);
        //return;
    }
    else 
    {
        const auto now = std::chrono::system_clock::now();
        time_t timer = std::chrono::system_clock::to_time_t(now);
        timer = std::time(0);
        std::tm local_tm;

        //local_tm = localtime_s(&currentTime);

        #if defined(__unix__)
                localtime_r(&timer, &local_tm);
        #elif defined(_MSC_VER)
                localtime_s(&local_tm, &timer);
        #else
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);
                local_tm = *std::localtime(&timer);     // typically not thread safe
        #endif

        int year = local_tm.tm_year + 1900;
        int month = local_tm.tm_mon + 1;
        int day = local_tm.tm_mday;
        int hour = local_tm.tm_hour;
        int minute = local_tm.tm_min;

        //int year = std::format("{:%Y}", now);
        //time_t timestamp;
        //time(&timestamp);
        //std::string asda = ctime(&timestamp);
        //std::string a = std::to_string(10);
        std::string yearStr = std::to_string(year);
        LPCSTR a = yearStr.c_str();
        SetWindowTextA(yearText, a);

        std::string monthStr = std::to_string(month);
        LPCSTR b = monthStr.c_str();
        SetWindowTextA(monthText, b);

        std::string dayStr = std::to_string(day);
        //LPCSTR a = yearStr.c_str();
        SetWindowTextA(dayText, dayStr.c_str());

        std::string hourStr = std::to_string(hour);
        //LPCSTR a = yearStr.c_str();
        SetWindowTextA(hourText, hourStr.c_str());

        std::string minuteStr = std::to_string(minute);
        //LPCSTR a = yearStr.c_str();
        SetWindowTextA(minuteText, minuteStr.c_str());

        //std::this_thread::sleep_for(std::chrono::seconds(10));
        MessageBox(NULL, L"update text called", NULL, MB_OK);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    //UpdateCurrentTime(yearText, monthText, dayText, hourText, minuteText);
}

bool InputScreen::InputScreenIsValid() {
    return baseWindow && caption && yearText && monthText && dayText && hourText && minuteText && submitButton;
}