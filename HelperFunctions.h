#pragma once
#include <chrono>
//#include <format>
#include <ctime>

class HelperFunctions
{
public:
    /*
        NOTE: year is number since 1900, months is number of months since January
    */
    static std::tm GetPresentTime()
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

        return local_tm;
    }
};

