#pragma once
#include "resource.h"
#include "framework.h"

class InputScreen
{
private:
	HWND baseWindow = nullptr;

	HWND caption = nullptr;
	HWND descriptionText = nullptr;
	HWND yearText = nullptr;
	HWND monthText = nullptr;
	HWND dayText = nullptr;
	HWND hourText = nullptr;
	HWND minuteText = nullptr;

	HWND presentDateButton = nullptr;
	HWND oneMonthCheck = nullptr;
	HWND oneWeekCheck = nullptr;
	HWND threeDayCheck = nullptr;
	HWND oneDayCheck = nullptr;
	HWND sixHourCheck = nullptr;
	HWND submitButton = nullptr;

	InputScreen(const InputScreen& other) = delete;	// no copy constructor
	InputScreen& operator=(const InputScreen& other) = delete;	// no copy assignment
	InputScreen(InputScreen&& other) = delete;	// no move constructor
	InputScreen& operator=(InputScreen&& other) = delete;	// no move assignment

	bool InputScreenIsValid();
	
public:
	//constructor
	InputScreen(LPCWSTR lpClassName, HINSTANCE hInstance, int nCmdShow);

	void ToggleCheckBox(int id);
	void UpdateCurrentTime();
	bool UploadInput();
	HWND GetBaseWindow();
	//destructor
	//~InputScreen();
	
};

