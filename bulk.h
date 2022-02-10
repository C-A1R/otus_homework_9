#ifndef BULK_H
#define BULK_H

#include "command_queue/CmdQueue.h"
#include "async.h"

#include <unordered_set>


/**
 * @brief Аккумулирует и управляет обработчиками команд 
 */
class BulkCommander
{
    /**
     * @brief Обработчик команд
     */
    class Bulk
    {
        std::unique_ptr<ICommandQueue> commands;
    public:
        Bulk(const size_t size);
        ~Bulk();

        /**
         * @brief Отправить команду в очередь
         */
        void push(const std::string &line);
    };

    std::unordered_set<Bulk *> _bulks;
public:
    BulkCommander() = default;
    ~BulkCommander();

    /**
     * @brief Создать обработчик команд
     */
    Bulk *createNewBulk(const size_t size);

    /**
     * @brief Отправить пакет команд определенному обработчику 
     */
    void push(async::handle_t handle, const char *data, std::size_t size);

    /**
     * @brief Удалить определнный обработчик команд
     */
    void removeBulk(async::handle_t handle);
};

#endif //BULK_H