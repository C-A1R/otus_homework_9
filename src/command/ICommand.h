#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>

/**
 * @brief Интерфейс команд
 */
class ICommand
{
public:
    ICommand() = default;
    virtual ~ICommand() = default;
    virtual void exec() = 0;
    virtual std::string getStr() const = 0;
};

#endif //ICOMMAND_H