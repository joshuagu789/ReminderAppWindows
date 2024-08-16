#include "ReminderProcesser.h"
#include "CustomMacros.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "shellapi.h"
#include <conio.h>

ReminderProcesser::ReminderProcesser(HWND hwnd) 
{

	NOTIFYICONDATA nid = {};
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	//nid.uFlags = NIF_ICON | NIF_TIP | NIF_GUID | NIF_MESSAGE | NIIF_RESPECT_QUIET_TIME;
	//nid.uFlags = NIF_TIP | NIF_GUID | NIIF_RESPECT_QUIET_TIME;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO;

	WCHAR temp[60] = L"C:/Users/joshu/source/repos/ReminderAppWindows/AppIcon.ico";
	temp[59] = '\0';
	LPWSTR temp2 = temp;

	nid.hIcon = (HICON)LoadImage(NULL, temp2, IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_SHARED);

	std::string name = "High Performance Gaming Reminder App";
	for (int i = 0; i < name.length(); i++) {
		nid.szTip[i] = name.at(i);
	}
	nid.szTip[name.length()] = '\0';

	//nid.szInfoTitle[0] = 'c';
	//nid.szInfo[0] = 'a';

	// This text will be shown as the icon's tooltip.
	//StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Test application");

	// Load the icon for high DPI.
	//LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_SMALL), LIM_SMALL, &(nid.hIcon));

	// Show the notification.
	if (Shell_NotifyIcon(NIM_ADD, &nid)) {
		//_getch();
		MessageBox(NULL, L"yay", NULL, MB_OK);
	}
	else {
		MessageBox(NULL, L"nooo", NULL, MB_OK);
	}
	//Shell_NotifyIcon(NIM_DELETE, &nid)
}


/*
	Assumes reminder encoding is like:
	Encode format is month-day-year-hour-minute-description-time_t-0-0-0-0-0  where 0's are booleans for if the reminder for 1 month, 1 week, 3 days, 1 day, or 6 hours
*/
void ReminderProcesser::ProcessReminders()
{
	std::fstream remindersFile;
	std::vector<std::string> reminders;
	std::queue<std::string> messagesToOutput;

	remindersFile.open(REMINDERS_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!remindersFile)
	{
		//MessageBox(NULL, L"Cannot find reminders.txt in ReminderProcesser", NULL, MB_OK);
		return;
	}

	std::string line = "";
	while (std::getline(remindersFile, line))
	{
		if (line.empty() || line.size() == 0) { return; }
		std::stringstream lineStream(line);
		std::vector<std::string> components;
		std::string component;
		components.reserve(12);
		while (std::getline(lineStream, component, '-'))
		{
			components.push_back(component);
		}
		// booleans are true if havent been notified of it yet
		bool oneMonth = components.at(7).at(0) - 48;	// character 0 has value 48, 48-48=0
		bool oneWeek = components.at(8).at(0) - 48;
		bool threeDay = components.at(9).at(0) - 48;
		bool oneDay = components.at(10).at(0) - 48;
		bool sixHour = components.at(11).at(0) - 48;
		bool present = true;

		const auto now = std::chrono::system_clock::now();
		time_t timer = std::chrono::system_clock::to_time_t(now);
		time_t finishTime = std::stol(components.at(6));

		long long difference = finishTime - timer;	//negative if finish time in past
		std::string notification = components.at(5) + " scheduled for " + components.at(0) + "/" + components.at(1) + "/" + components.at(2) + " (Month/Day/Year) at time " 
									+ components.at(3) + ":" + components.at(4) + " (24 Hour Time Notation)";

		if (oneMonth && difference <= ONE_MONTH_AS_SECONDS) {
			messagesToOutput.push("One Month Reminder: " + notification);
			oneMonth = false;
			components.at(7) = '0';
		}
		if (oneWeek && difference <= ONE_WEEK_AS_SECONDS) {
			messagesToOutput.push("One Week Reminder: " + notification);
			oneWeek = false;
			components.at(8) = '0';
		}
		if (threeDay && difference <= THREE_DAYS_AS_SECONDS) {
			messagesToOutput.push("Three Day Reminder: " + notification);
			threeDay = false;
			components.at(9) = '0';
		}
		if (oneDay && difference <= ONE_DAY_AS_SECONDS) {
			messagesToOutput.push("One Day Reminder: " + notification);
			oneDay = false;
			components.at(10) = '0';
		}
		if (sixHour && difference <= SIX_HOURS_AS_SECONDS) {
			messagesToOutput.push("Six Hour Reminder: " + notification);
			sixHour = false;
			components.at(11) = '0';
		}
		if (difference <= 0) {
			messagesToOutput.push("Reminder's Deadline: " + notification);
			present = false;
			//oneMonth = false;
			//components.at(7) = '0';
		}
		// keeping notification rather than discarding it
		if (oneMonth || oneWeek || threeDay || oneDay || sixHour || present) {
			std::string newLine = components.at(0);
			for (int x = 1; x <= 11; x++) {
				newLine += '-' + components.at(x);
			}
			reminders.push_back(newLine);
		}
		
	}
	remindersFile.close();

	// sending out notifications
	while (!messagesToOutput.empty()) 
	{
		std::string message = messagesToOutput.front();
		messagesToOutput.pop();
		WCHAR temp[MAX_LOADSTRING];
		int i = 0;
		while(i < message.length()){
			temp[i] = message.at(i);
			i++;
		}
		temp[i] = '\0';
		LPWSTR pointer = temp;

		MessageBox(NULL, pointer, NULL, MB_OK);
		/*
		NOTIFYICONDATA notification = {};
		Shell_NotifyIcon(NIM_ADD, &notification);
		char temp2[MAX_LOADSTRING];

		//notification.szInfoTitle;
		for (int i = 0; i < message.length(); i++) {
			notification.szInfo[i] = message[i];
		}
		*/
			
	}

	// regenerating text file reminders.txt
	std::ofstream newRemindersFile(REMINDERS_FILE_NAME);
	for (auto& str : reminders) {
		newRemindersFile << str + "\n";
	}
	
	newRemindersFile.close();

	//MessageBox(NULL, L"done processing in ReminderProcesser", NULL, MB_OK);
}
//#define ONE_MONTH_AS_SECONDS 2592000	// 30 days
//#define ONE_WEEK_AS_SECONDS 604800
//#define THREE_DAYS_AS_SECONDS 259200
//#define ONE_DAY_AS_SECONDS 86400
//#define SIX_HOURS_AS_SECONDS 21600