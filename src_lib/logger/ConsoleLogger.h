#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ILogger.h"

#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>


/**
 * @brief Логгер, который пишет в консоль
 */
class ConsoleLogger : public ILogger
{
    std::condition_variable _cv;
    std::mutex _mtx;
    std::queue<std::string> _logs;
    std::thread _thread;
    std::atomic<bool> _stoped {false};

public:
    ConsoleLogger();
    ~ConsoleLogger();
    void pushLog(const time_t &, const std::string &log) override;

private:
    void worker();
};

#endif //CONSOLELOGGER_H