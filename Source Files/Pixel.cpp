#include "../Header Files/Pixel.h"

Pixel::Pixel()
{
    red = 0;
    green = 0;
    blue = 0;
}

Pixel::Pixel(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Pixel::Pixel(std::string hexCode)
{
    if (hexCode[0] != HEX_CODE_START_SYMBOL)
    {
        throw std::invalid_argument("The first character of a hex string should be '#'");
    }
    //if (!isValidHexadecimalNumber(hexCode))
    //{
       // throw std::invalid_argument("Invalid hex string");
    //}
    if (hexCode.length() != HEX_CODE_LENGTH)
    {
        throw std::invalid_argument("Invalid length of a hex string.(should be #RRGGBB)");
    }

    red = hexToDecimal(hexCode.substr(1, 2));
    green = hexToDecimal(hexCode.substr(3, 2));
    blue = hexToDecimal(hexCode.substr(5, 2));
}

int Pixel::hexToDecimal(std::string hexCode)
{
    int result = 0;
    for (int i = 0; i < hexCode.length(); ++i)
    {
        if (hexCode[i] >= 48 && hexCode[i] <= 57)
        {
            result += (hexCode[i] - 48) * pow(16, hexCode.length() - i - 1);
        }
        else if (hexCode[i] >= 65 && hexCode[i] <= 70)
        {
            result += (hexCode[i] - 55) * pow(16, hexCode.length() - i - 1);
        }
        else if (hexCode[i] >= 97 && hexCode[i] <= 102)
        {
            result += (hexCode[i] - 87) * pow(16, hexCode.length() - i - 1);
        }
    }
    return result;
}

bool isValidHexSymbol(const char ch)
{
    return ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F') ||
           ('0' <= ch && ch <= '9');
}

bool isValidHexadecimalNumber(const std::string &str)
{
    for (std::size_t i = 0; i < str.length(); ++i)
    {
        if (!isValidHexSymbol(str[i]))
        {
            return false;
        }
    }

    return str.length() != 0;
}