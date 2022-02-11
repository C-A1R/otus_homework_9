
#include "MacroCmd.h"

void MacroCmd::addCmd(std::unique_ptr<ICommand> cmd)
{
    _commands.emplace_back(std::move(cmd));
}

void MacroCmd::exec()
{
    for (const auto &c : _commands)
    {
        c->exec();
    }
}

std::string MacroCmd::getStr() const
{
    std::string result;
    for (size_t i = 0; i < _commands.size(); ++i)
    {
        result += _commands.at(i)->getStr();
        if (i != _commands.size() - 1)
        {
            result += ", ";
        }
    }
    return result;
}
