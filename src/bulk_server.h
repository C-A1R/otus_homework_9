#ifndef BULK_SERVER_H
#define BULK_SERVER_H

#include "boost/asio.hpp"

class ICommandQueue;

using boost::asio::ip::tcp;

class BulkServer : public std::enable_shared_from_this<BulkServer>
{
    std::mutex _mtx;
    tcp::acceptor _acceptor;
    std::shared_ptr<ICommandQueue> _commandsQueue;
public:
    BulkServer(boost::asio::io_context &io_context, short port, size_t bulkSize);
    void pushCommand(const std::string &cmd);
private:
    void do_accept();
};


#endif //BULK_SERVER_H