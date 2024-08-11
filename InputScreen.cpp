#include "InputScreen.h"
#include "combaseapi.h"
#include "WinUser.h"
#include "CustomMacros.h"
#include "HelperFunctions.h"

#include <iostream>
#include <chrono>
#include <format>
#include <ctime>
#include <string>
#include <thread>
#include <cwctype>

//void UpdateCurrentTime(HWND yearText, HWND monthText, HWND dayText, HWND hourText, HWND minuteText);    //forward declaration

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

    presentDateButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Current Time",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        100,         // x position 
        200,         // y position 
        100,        // Button width
        100,        // Button height
        baseWindow,     // Parent window
        (HMENU)SET_PRESENT_DATE,       // menu
        (HINSTANCE)GetWindowLongPtr(baseWindow, GWLP_HINSTANCE),
        NULL);

    if (!presentDateButton)
    {
        MessageBox(NULL, L"error: presentDateButton is nullptr for InputScreen", NULL, MB_OK);
        return;
    }

    submitButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"SUBMIT DATE",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        200,         // x position 
        200,         // y position 
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
        L"Year:              Month:              Day:                  Hour:               Minute:               Description:",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER | WS_CAPTION,  // Styles 
        100,         // x position 
        50,         // y position 
        900,        //  width
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

    descriptionText = CreateWindowEx(
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        L"Edit",  // Predefined class; Unicode assumed, ListBox if want to display info without editing 
        L"",      // Button text 
        WS_VISIBLE | WS_CHILD | WS_BORDER,  // Styles 
        600,         // x position 
        100,         // y position 
        400,        //  width
        100,        // height
        baseWindow,     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);

    if (!descriptionText)
    {
        MessageBox(NULL, L"error: descriptionText is nullptr for InputScreen", NULL, MB_OK);
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
    //UpdateCurrentTime();
    //MessageBox(NULL, L"what happen1", NULL, MB_OK);
    //UpdateCurrentTime(yearText, monthText, dayText, hourText, minuteText);
    //MessageBox(NULL, L"what happen2", NULL, MB_OK);
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::thread updater(UpdateCurrentTime, yearText, monthText, dayText, hourText, minuteText);
    //updater.join();
}
/*
InputScreen::~InputScreen() 
{
    delete baseWindow;
    HWND descriptionText = nullptr;
    HWND yearText = nullptr;
    HWND monthText = nullptr;
    HWND dayText = nullptr;
    HWND hourText = nullptr;
    HWND minuteText = nullptr;

    HWND presentDateButton = nullptr;
    HWND submitButton = nullptr;
    delete caption;
    delete descriptionText;
    delete yearText;
    delete monthText;
    delete dayText;
    delete hourText;
    delete minuteText;
    delete presentDateButton;
    delete submitButton;
}
*/
void InputScreen::UpdateCurrentTime() {
//void UpdateCurrentTime(HWND yearText, HWND monthText, HWND dayText, HWND hourText, HWND minuteText) {

    //if (!InputScreenIsValid()) 
    //{
    //    MessageBox(NULL, L"error: invalid input screen on UpdateCurrentTime's call to InputScreenIsValid in InputScreen", NULL, MB_OK);
    //    return;
    //}

    if (!InputScreenIsValid()) {
        MessageBox(NULL, L"error: invalid input screen on UpdateCurrentTime's call to InputScreenIsValid in InputScreen", NULL, MB_OK);
        //return;
    }
    else 
    {
        /*
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
        */
        std::tm local_tm = HelperFunctions::GetPresentTime(); 
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
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //UpdateCurrentTime(yearText, monthText, dayText, hourText, minuteText);
}

bool InputScreen::InputScreenIsValid() {
    return baseWindow && caption && yearText && monthText && dayText && hourText && minuteText && submitButton && descriptionText;
}

bool InputScreen::UploadInput()
{
    //if (!yearText || !monthText || !dayText || !hourText || !minuteText || !descriptionText) { return false; }
    if (!InputScreenIsValid()) {
        MessageBox(NULL, L"Warning: invalid input screen", NULL, MB_OK);
        return false;
    }

    HWND numericalInputs[5]{yearText, monthText, dayText, hourText, minuteText};
    int inputLengths[5] = { 0 };
    std::string values[5] = { "" };

    //for (HWND text : numericalInputs)
    for (int x = 0; x < 5; x++) 
    {
        HWND text = numericalInputs[x];
        WCHAR a[MAX_LOADSTRING];
        LPWSTR temp = a;
        GetWindowTextW(text, temp, 1000);

        int length = GetWindowTextLengthA(text);
        inputLengths[x] = length;
        
        for (int i = 0; i < length; i++) 
        {
            WCHAR character = a[i];
            if (!std::iswdigit(character)) 
            {
                std::wstring error = L"Warning: non-number input detected for ";
                error += std::wstring(a);
                MessageBox(NULL, error.c_str(), NULL, MB_OK);
                return false;
            }
        }
        for (int j = 0; j < length; j++)
        {
            values[x] += a[j];
        }
    }

    if (inputLengths[0] > 4 || inputLengths[1] > 2 || inputLengths[2] > 2 || inputLengths[3] > 2 || inputLengths[4] > 2)
    {
        MessageBox(NULL, L"Warning: too many digits in a number field", NULL, MB_OK);
        return false;
    }
    if (inputLengths[0] == 0 || inputLengths[1] == 0 || inputLengths[2] == 0 || inputLengths[3] == 0 || inputLengths[4] == 0)
    {
        MessageBox(NULL, L"Warning: input field is empty", NULL, MB_OK);
        return false;
    }
    // character 0 is 48, character 9 is 57
    /*
    int year = StringToInteger(values[0]);
    int month = StringToInteger(values[1]);
    int day = StringToInteger(values[2]);
    int hour = StringToInteger(values[3]);
    int minute = StringToInteger(values[4]);
    */
    int year = std::stoi(values[0]);
    int month = std::stoi(values[1]);
    int day = std::stoi(values[2]);
    int hour = std::stoi(values[3]);
    int minute = std::stoi(values[4]);

    if (year > 2100) 
    {
        MessageBox(NULL, L"Warning: I will be like super old at this time", NULL, MB_OK);
        return false;
    }
    if (year < 2024)
    {
        MessageBox(NULL, L"Warning: I dont like have a time machine", NULL, MB_OK);
        return false;
    }
    if (month < 1 || month >= 12) 
    {
        MessageBox(NULL, L"Warning: invalid value for month", NULL, MB_OK);
        return false;
    }
    if (day < 1 || day > 31) {
        MessageBox(NULL, L"Warning: invalid day", NULL, MB_OK);
        return false;
    }
    if (hour < 0 || hour >= 24)
    {
        MessageBox(NULL, L"Warning: invalid value for hour", NULL, MB_OK);
        return false;
    }
    if (minute < 0 || minute >= 60)
    {
        MessageBox(NULL, L"Warning: invalid value for minute", NULL, MB_OK);
        return false;
    }
    /*
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
    */
    //struct tm date {0, minute, hour, day, month-1, year-1900};
    struct tm date;
    date.tm_min = minute;
    date.tm_hour = hour;
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    struct tm current = HelperFunctions::GetPresentTime();

    time_t date_t = mktime(&date);
    time_t current_t = mktime(&current);

    double difference = std::difftime(date_t, current_t);
    int diff = difference;
    double omg = std::difftime(date_t, date_t);

    MessageBox(NULL, L"success?", NULL, MB_OK);
}