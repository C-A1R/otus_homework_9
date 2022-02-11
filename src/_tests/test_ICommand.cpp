#define BOOST_TEST_MODULE test_ICommand

#include "../command/Cmd.h"
#include "../command/MacroCmd.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_Cmd)

BOOST_AUTO_TEST_CASE(getStr)
{
    Cmd cmd("cmd1");
    BOOST_CHECK(cmd.getStr() == "cmd1");
}

BOOST_AUTO_TEST_SUITE_END() 


BOOST_AUTO_TEST_SUITE(test_MacroCmd)

BOOST_AUTO_TEST_CASE(getStr_empty)
{
    MacroCmd macros;
    BOOST_CHECK(macros.getStr().empty());
}
BOOST_AUTO_TEST_CASE(getStr_single)
{
    MacroCmd macros;
    macros.addCmd(std::make_unique<Cmd>("cmd1"));
    BOOST_CHECK(macros.getStr() == "cmd1");
}
BOOST_AUTO_TEST_CASE(getStr_multi)
{
    MacroCmd macros;
    macros.addCmd(std::make_unique<Cmd>("cmd1"));
    macros.addCmd(std::make_unique<Cmd>("cmd2"));
    macros.addCmd(std::make_unique<Cmd>("cmd3"));
    macros.addCmd(std::make_unique<Cmd>("cmd4"));
    BOOST_CHECK(macros.getStr() == "cmd1, cmd2, cmd3, cmd4");
}

BOOST_AUTO_TEST_SUITE_END() 