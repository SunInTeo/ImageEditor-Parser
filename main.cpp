#include "./Header Files/CommandHandler.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        CommandHandler cmdHndlr;
        cmdHndlr.startReading();
    }
    else if (argc == 2)
    {
        CommandHandler cmdHndlr((std::string)argv[1]);
        cmdHndlr.startReading();
    }
    else
    {
        std::cerr << "Too many arguments!\n";
        return 1;
    }

    return 0;
}