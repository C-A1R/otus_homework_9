#ifndef CMD_H
#define CMD_H

#include "ICommand.h"

/**
 * @brief Обычная команда
 */
class Cmd : public ICommand
{
    const std::string _str;
public:
    Cmd(const std::string &str);
    void exec() override;
    std::string getStr() const override;
};

#endif //CMD_H