
#include "ConsoleLogger.h"

#include <iostream>


ConsoleLogger::ConsoleLogger()
{
    _thread = std::thread(&ConsoleLogger::worker, this);
}

ConsoleLogger::~ConsoleLogger()
{
    _stoped = true;
    _cv.notify_one();
    _thread.join();
}

void ConsoleLogger::pushLog(const time_t &, const std::string &log) 
{
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _logs.push(log);
    }
    _cv.notify_one();
}

void ConsoleLogger::worker() 
{
    auto printNext = [this]()
    {
        if (_logs.empty())
            return;
        std::cout << _logs.front() << std::endl;
        _logs.pop();
    };

    while (!_stoped)
    {
        std::unique_lock<std::mutex> lock(_mtx);
        while (!_stoped && _logs.empty())
        {
            _cv.wait(lock);
        }
        if (_stoped)
        {
            break;
        }
        printNext();
    }
    while (!_logs.empty())
    {
        printNext();
    }
}
