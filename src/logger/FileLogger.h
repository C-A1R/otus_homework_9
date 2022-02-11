#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "ILogger.h"

#include <queue>
#include <condition_variable>
#include <thread>
#include <atomic>


/**
 * @brief Логгер, который пишет в файл
 */
class FileLogger : public ILogger
{
    std::condition_variable _cv;
    std::mutex _mtx;
    std::queue<std::pair<time_t, std::string> > _logs;
    std::thread _thread_1;
    std::thread _thread_2;
    std::atomic<bool> _stoped {false};
    std::atomic<int> _count {0};

public:
    FileLogger();
    ~FileLogger();
    void pushLog(const time_t &time, const std::string &log) override;

private:
    void worker();
    void printNext();
};

#endif //FILELOGGER_H