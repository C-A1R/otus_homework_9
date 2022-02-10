#include "FileLogger.h"

#include <fstream>
#include <sstream>


FileLogger::FileLogger()
{
    _thread_1 = std::thread(&FileLogger::worker, this);
    _thread_2 = std::thread(&FileLogger::worker, this);
}

FileLogger::~FileLogger()
{
    _stoped = true;
    _cv.notify_all();
    _thread_1.join();
    _thread_2.join();
}

void FileLogger::pushLog(const time_t &time, const std::string &log) 
{
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _logs.push(std::make_pair(time, log));
    }
    _cv.notify_one();
}

void FileLogger::worker() 
{
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

void FileLogger::printNext() 
{
    if (_logs.empty())
    {
        return;
    }
    auto pair = _logs.front();
    _logs.pop();

    std::stringstream ss;
    ss << std::this_thread::get_id();

    std::string filename = "bulk" + std::to_string(pair.first) + " " + std::to_string(++_count)
                                  + " thread-" + ss.str() + ".log";
    if (filename.empty() || pair.second.empty())
    {
        return;
    }
    std::ofstream outfile(filename);
    outfile << pair.second << std::endl;
    outfile.close();
}
