#define BOOST_TEST_MODULE test_ICommand

#include "../command/Cmd.h"
#include "../command/MacroCmd.h"
#include "../command_queue/CmdQueue.h"
#include "../logger/ILogger.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_cmdQueue)

BOOST_AUTO_TEST_CASE(blockSize_0)
{
    CmdQueue cmdQueue(0);
    BOOST_CHECK(cmdQueue.size() == 0);

    cmdQueue.push(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(cmdQueue.size() == 0);

    cmdQueue.startMacros();
    BOOST_CHECK(!cmdQueue.haveStartedMacroses());
}

BOOST_AUTO_TEST_CASE(blockSize_1)
{
    CmdQueue cmdQueue(1);
    cmdQueue.push(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(cmdQueue.size() == 0);

    cmdQueue.startMacros();
    cmdQueue.push(std::make_unique<Cmd>("cmd2"));
    cmdQueue.push(std::make_unique<Cmd>("cmd3"));
    BOOST_CHECK(cmdQueue.haveStartedMacroses());
    cmdQueue.finishMacros();
    BOOST_CHECK(!cmdQueue.haveStartedMacroses());
    BOOST_CHECK(cmdQueue.size() == 0);
}

BOOST_AUTO_TEST_CASE(blockSize_several_static)
{
    CmdQueue cmdQueue(3);
    cmdQueue.push(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(cmdQueue.size() == 1);
    cmdQueue.push(std::make_unique<Cmd>("cmd2"));
    BOOST_CHECK(cmdQueue.size() == 2);
    cmdQueue.push(std::make_unique<Cmd>("cmd3"));
    BOOST_CHECK(cmdQueue.size() == 0);

    cmdQueue.push(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(cmdQueue.size() == 1);
    cmdQueue.push(nullptr);
    BOOST_CHECK(cmdQueue.size() == 0);
}

BOOST_AUTO_TEST_CASE(blockSize_several_dynamic)
{
    CmdQueue cmdQueue(3);
    cmdQueue.push(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(cmdQueue.size() == 1);
    cmdQueue.push(std::make_unique<Cmd>("cmd2"));
    BOOST_CHECK(cmdQueue.size() == 2);

    cmdQueue.startMacros();
    BOOST_CHECK(cmdQueue.size() == 0);
    cmdQueue.push(std::make_unique<Cmd>("cmd3"));
    BOOST_CHECK(cmdQueue.size() == 0);
    BOOST_CHECK(cmdQueue.haveStartedMacroses());
    cmdQueue.push(std::make_unique<Cmd>("cmd4"));
    BOOST_CHECK(cmdQueue.size() == 0);
    BOOST_CHECK(cmdQueue.haveStartedMacroses());
    cmdQueue.finishMacros();
    BOOST_CHECK(cmdQueue.size() == 0);
    BOOST_CHECK(!cmdQueue.haveStartedMacroses());

    cmdQueue.startMacros();
    cmdQueue.push(std::make_unique<Cmd>("cmd5"));
    cmdQueue.push(std::make_unique<Cmd>("cmd6"));
    cmdQueue.startMacros();
    cmdQueue.push(std::make_unique<Cmd>("cmd7"));
    cmdQueue.push(std::make_unique<Cmd>("cmd8"));
    cmdQueue.finishMacros();
    BOOST_CHECK(cmdQueue.haveStartedMacroses());
    cmdQueue.push(std::make_unique<Cmd>("cmd9"));
    cmdQueue.finishMacros();
    BOOST_CHECK(cmdQueue.size() == 0);
    BOOST_CHECK(!cmdQueue.haveStartedMacroses());

    cmdQueue.startMacros();
    cmdQueue.push(std::make_unique<Cmd>("cmd10"));
    cmdQueue.push(nullptr);
    BOOST_CHECK(cmdQueue.size() == 0);
    BOOST_CHECK(!cmdQueue.haveStartedMacroses());
}

BOOST_AUTO_TEST_SUITE_END() 