#ifndef SESSION_H
#define SESSION_H

#include "boost/asio.hpp"

#include <queue>

class ICommand;
class ICommandQueue;

using boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
    tcp::socket _socket;
    enum {max_length = 1024};
    char _data[max_length];
    std::shared_ptr<ICommandQueue> _commandsQueue;
    std::mutex &_m;
    std::queue<std::unique_ptr<ICommand> > _macroQueue;
    bool _macroEnabled{false};
public:
    Session(tcp::socket socket, const std::shared_ptr<ICommandQueue> &queue, std::mutex &m);
    void start();
private:
    void do_read();
    void parseData(size_t length);
    void pushLine(const std::string &line);
};

#endif //SESSION_H