#include "bulk.h"

#include "command/Cmd.h"
#include "command/MacroCmd.h"
#include "logger/ConsoleLogger.h"
#include "logger/FileLogger.h"

#include <cstring>
#include <cassert>


BulkCommander::Bulk::Bulk(const size_t size)
{
    assert(size > 0);
    commands = std::make_unique<CmdQueue>(size);
    commands->addLogger(std::make_unique<ConsoleLogger>());
    commands->addLogger(std::make_unique<FileLogger>());
}

BulkCommander::Bulk::~Bulk()
{
    commands->push(nullptr);
}

void BulkCommander::Bulk::push(const std::string &line)
{
    if (line.empty())
    {
        commands->push(nullptr);
    }
    else if (line == "{")
    {
        commands->startMacros();
    }
    else if (line == "}")
    {
        commands->finishMacros();
    }
    else
    {
        commands->push(std::make_unique<Cmd>(line));
    }
}

BulkCommander::~BulkCommander()
{
    for(auto b : _bulks)
    {
        delete b;
    }
}

BulkCommander::Bulk *BulkCommander::createNewBulk(const size_t size) 
{
    auto bulk = new Bulk(size);
    _bulks.insert(bulk);
    return bulk;
}


void BulkCommander::push(async::handle_t handle, const char *data, std::size_t size) 
{
    if (!handle)
    {
        return;
    }
    auto i = _bulks.find(reinterpret_cast<Bulk *>(handle));
    if (i == _bulks.cend())
    {
        return;
    }

    auto bulk = *i; 
    auto str = std::string(data, size);
    while (!str.empty())
    {
        auto i = str.find("\n");
        if (i == std::string::npos)
        {
            bulk->push(str);
            str.clear();
            break;
        }
        bulk->push(str.substr(0, i));
        str = str.substr(i + std::strlen("\n"), std::string::npos);
    }
}

void BulkCommander::removeBulk(async::handle_t handle)
{
    if (!handle)
    {
        return;
    }
    auto i = _bulks.find(reinterpret_cast<Bulk *>(handle));
    if (i == _bulks.cend())
    {
        return;
    }
    delete *i;
    _bulks.erase(i);
}
