#include "bulk_server.h"

#include <cassert>

int main(int argc, char *argv[])
{
    assert(argc == 3);
    short port {0};
    size_t bulkSize {0};
    std::stringstream sstr;
    sstr << argv[1] << ' ' << argv[2];
    sstr >> port >> bulkSize;
    assert(bulkSize > 0);

    boost::asio::io_context io_context;
    auto server = BulkServer(io_context, port, bulkSize);
    io_context.run();
    return 0;
}