#include "../Header Files/Utils.h"

std::string toUpper(const std::string &str)
{
    std::string tempStr = str;
    for (size_t i = 0; i < tempStr.length(); ++i)
    {
        if (tempStr[i] >= 'a' && tempStr[i] <= 'z')
        {
            tempStr[i] -= ('a' - 'A');
        }
    }
    return tempStr;
}

bool stringContains(std::string &str, char c)
{
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == c)
        {
            return true;
        }       
    }
    return false;
}

void trimWordsAfterGivenCharFromString(std::string &str, char c)
{
    while (str[str.size() - 1] != c)
    {
        str.pop_back();
    }
    str.pop_back();
}

void goToNextLine(std::ifstream &in)
{
    std::string str;
    getline(in, str);
}

std::string getNextParameter(std::ifstream &in)
{
    std::string bufferStr;
    in >> bufferStr;

    if (!in)
    {
        return nullptr;
    }

    if (stringContains(bufferStr, '#'))
    {
        if (bufferStr[0] != '#')
        {
            trimWordsAfterGivenCharFromString(bufferStr, '#');
            goToNextLine(in);
            return bufferStr;
        }
        else
        {
            goToNextLine(in);
            return getNextParameter(in);
        }
    }
    else
    {
        return bufferStr;
    }

    return nullptr;
}

std::string getImageExtension(const std::string &path)
{
    if (path.size() < PATH_SIZE)
    {
        throw std::invalid_argument("Incorrect path size");
    }
        
    if (path[path.size() - 4] != '.')
    {
        throw std::invalid_argument("No given extension");
    }
        
    return path.substr(path.size() - 3, path.size());
}
