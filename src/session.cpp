#include "session.h"
#include "command_queue/CmdQueue.h"

Session::Session(tcp::socket socket, const std::shared_ptr<ICommandQueue> &queue, std::mutex &m)
    : _socket{std::move(socket)}, _commandsQueue{queue}, _m{m}
{
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length), 
        [this, self](boost::system::error_code ec, size_t length)
        {
            if (!ec)
            {
                parseData(length);
            }
        });
}

void Session::parseData(size_t length)
{
    auto str = std::string(_data, length);
    while (!str.empty())
    {
        auto i = str.find("\n");
        if (i == std::string::npos)
        {
            pushLine(str);
            str.clear();
            break;
        }
        pushLine(str.substr(0, i));
        str = str.substr(i + std::strlen("\n"), std::string::npos);
    }
    pushLine("");
}

void Session::pushLine(const std::string &line) 
{
    auto _pushCmd = [this](std::unique_ptr<Cmd> cmd)
    {
        std::lock_guard<std::mutex> lock(_m);
        _commandsQueue->push(std::move(cmd));
    };
    auto _pushMacro = [this]()
    {
        if (_macroQueue.empty())
        {
            return;
        }
        std::lock_guard<std::mutex> lock(_m);
        _commandsQueue->startMacros();
        while(!_macroQueue.empty())
        {
            _commandsQueue->push(std::move(_macroQueue.front()));
            _macroQueue.pop();
        }
        _commandsQueue->finishMacros();
    };


    if (line.empty())
    {
        _pushMacro();
        _commandsQueue->push(nullptr);
    }
    else if (line == "{")
    {
        _macroEnabled = true;
    }
    else if (line == "}")
    {
        _pushMacro();
        _macroEnabled = false;
    }
    else
    {
        _macroEnabled ? _macroQueue.push(std::make_unique<Cmd>(line))
                      : _pushCmd(std::make_unique<Cmd>(line));
    }
}