#include "async.h"

#include "bulk.h"

#include <cassert>


namespace async 
{
    BulkCommander commander;

    handle_t connect(std::size_t bulk) 
    {
        assert(bulk > 0);
        auto b = commander.createNewBulk(bulk);
        return b;
    }

    void receive(handle_t handle, const char *data, std::size_t size) 
    {
        commander.push(handle, data, size);
    }

    void disconnect(handle_t handle) 
    {
        commander.removeBulk(handle);
    }
}
