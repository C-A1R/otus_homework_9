#ifndef ICOMMANDQUEUE_H
#define ICOMMANDQUEUE_H

#include <memory>

class ICommand;
class ILogger;


/**
 * @brief Интерфейс очереди команд
 */
class ICommandQueue
{
public:
    ICommandQueue() = default;
    virtual ~ICommandQueue() = default;

    /**
     * @brief Добавить команду в очередь
     */
    virtual void push(std::unique_ptr<ICommand> cmd) = 0;

    /**
     * @brief Начать запись макро-команды 
     */
    virtual void startMacros() = 0;

    /**
     * @brief Закончить запись макро-команды 
     */
    virtual void finishMacros() = 0;

    /**
     * @brief Количество команд в очереди
     */
    virtual size_t size() const = 0;

    /**
     * @brief Есть ли начатая макрокоманда
     */
    virtual bool haveStartedMacroses() const = 0;

    /**
     * @brief Добавить логгер
     */
    virtual void addLogger(std::unique_ptr<ILogger> logger) = 0;

private:
    /**
     * @brief Выполнить всю очередь команд
     */
    virtual void execCommands() = 0;
};

#endif //ICOMMANDQUEUE_H