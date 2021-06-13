#include "../Header Files/Command.h"

Command::Command(std::string raw)
{
    rawString = raw;

    bool quoteMode = false;
    std::string newStr;
    for (size_t i = 0; i < strlen(raw.c_str()); ++i)
    {
        if (raw[i] == ' ' && (i != 0 && raw[i - 1] != ' ') && !quoteMode)
        {
            arrString.push_back(newStr);
            newStr.clear();
        }
        else if (raw[i] == '"')
        {
            quoteMode = !quoteMode;
        }
        else if (raw[i] != ' ' || quoteMode)
        {
            newStr.push_back(raw[i]);
        }
    }

    arrString.push_back(newStr);
}

std::string Command::getCommand()
{
    return rawString;
}
int Command::getSize() const
{
    return (int)arrString.size();
}

void Command::print()
{
    std::cout << "[";
    const size_t len = arrString.size();
    for (size_t i = 0; i < len; ++i)
    {
        std::cout << arrString[i];
        if (i != len - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

std::string &Command::operator[](std::size_t pos)
{
    return arrString[pos];
}
const std::string &Command::operator[](std::size_t pos) const
{
    return arrString[pos];
}