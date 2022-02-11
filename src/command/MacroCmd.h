#ifndef MACROCMD_H
#define MACROCMD_H

#include "ICommand.h"

#include <memory>
#include <vector>

/**
 * @brief Макрокоманда, которая может состоять из нескольких обычных команд
 */
class MacroCmd : public ICommand
{   
    std::vector<std::unique_ptr<ICommand> > _commands;
public:
    MacroCmd() = default;
    void addCmd(std::unique_ptr<ICommand> cmd);
    void exec() override;
    std::string getStr() const override;
};

#endif //MACROCMD_H