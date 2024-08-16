#pragma once
#include "resource.h"
#include "framework.h"
#include "shellapi.h"
#include <unordered_set>
#include <string>
#include <queue>


class ReminderProcesser
{
private:
	//std::fstream remindersFile;

	//std::unordered_set<std::string> reminders;
	//std::queue<std::string> messagesToOutput;
	//NOTIFYICONDATA balloon;
	//std::unique_ptr<NOTIFYICONDATA> balloon;

	ReminderProcesser(const ReminderProcesser& other) = delete;	// no copy constructor
	ReminderProcesser& operator=(const ReminderProcesser& other) = delete;	// no copy assignment
	ReminderProcesser(ReminderProcesser&& other) = delete;	// no move constructor
	ReminderProcesser& operator=(ReminderProcesser&& other) = delete;	// no move assignment
public:
	ReminderProcesser();
	static void ProcessReminders(NOTIFYICONDATA& balloon);
};

