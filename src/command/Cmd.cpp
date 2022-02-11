#include "Cmd.h"

Cmd::Cmd(const std::string &str) : _str{str} 
{
}

void Cmd::exec() 
{
}

std::string Cmd::getStr() const
{
    return _str;
}

