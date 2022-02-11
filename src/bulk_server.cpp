#include "bulk_server.h"
#include "session.h"
#include "command_queue/CmdQueue.h"
#include "logger/ConsoleLogger.h"
#include "logger/FileLogger.h"


BulkServer::BulkServer(boost::asio::io_context &io_context, short port, size_t bulkSize)
    : _acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
    , _commandsQueue{std::make_shared<CmdQueue>(bulkSize)}
{
    _commandsQueue->addLogger(std::make_unique<ConsoleLogger>());
    _commandsQueue->addLogger(std::make_unique<FileLogger>()); 
    do_accept();
}

void BulkServer::pushCommand(const std::string &cmd)
{
    std::lock_guard<std::mutex> lock(_mtx);
    _commandsQueue->push(std::make_unique<Cmd>(cmd));
}

void BulkServer::do_accept()
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::make_shared<Session>(std::move(socket), _commandsQueue, _mtx)->start();
        }
        do_accept();
    });
}
