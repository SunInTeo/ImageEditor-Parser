#define CATCH_CONFIG_MAIN
#include "../Header files/Command.h"
#include "./catch2.hpp"

TEST_CASE("Splitting commands")
{
    SECTION("Correct Input(single word)")
    {
        Command command("Sample");
        REQUIRE(command[0] == "Sample");
    }
    SECTION("Correct input(multiple words with single spaces between the words)")
    {
        Command command("Sample1 Sample2 Sample3");
        REQUIRE(command[0] == "Sample1");
        REQUIRE(command[1] == "Sample2");
        REQUIRE(command[2] == "Sample3");
    }

    SECTION("Correct input(multiple words with multiple spaces between the words)")
    {
        Command command("Sample1  Sample2   Sample3");
        REQUIRE(command[0] == "Sample1");
        REQUIRE(command[1] == "Sample2");
        REQUIRE(command[2] == "Sample3");
    }

    SECTION("Correct input in quotes(single word in them)")
    {
        Command command("\"Sample\"");
        REQUIRE(command[0] == "Sample");
    }
    SECTION("Correct input in quotes(multiple words in them)")
    {
        Command command("\"Sample1 Sample2 Sample3\"");
        REQUIRE(command[0] == "Sample1 Sample2 Sample3");
    }
    SECTION("Correct input in quotes(multiple words in them and multiple spaces between the words)")
    {
        Command command("\"Sample1  Sample2   Sample3\"");
        REQUIRE(command[0] == "Sample1  Sample2   Sample3");
    }

}
