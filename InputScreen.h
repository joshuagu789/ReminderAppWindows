#pragma once
#include "resource.h"
#include "framework.h"

class InputScreen
{
private:
	HWND baseWindow = nullptr;

	HWND caption = nullptr;
	HWND yearText = nullptr;
	HWND monthText = nullptr;
	HWND dayText = nullptr;
	HWND hourText = nullptr;
	HWND minuteText = nullptr;

	HWND submitButton = nullptr;

	//InputScreen(const InputScreen& other) = delete;	// no copy constructor
	//InputScreen& operator=(const InputScreen& other) = delete;	// no copy assignment
	//InputScreen(InputScreen&& other) = delete;	// no move constructor
	//InputScreen& operator=(InputScreen&& other) = delete;	// no move assignment

	bool InputScreenIsValid();
	//void UpdateCurrentTime();
public:
	//constructor
	InputScreen(LPCWSTR lpClassName, HINSTANCE hInstance, int nCmdShow);
	//destructor
	//~InputScreen();
	
};

