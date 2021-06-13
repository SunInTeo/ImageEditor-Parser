/** @file Exceptions.h
 *  @brief Provides different exceptions.
 *
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */
#pragma once

#include <iostream>

class NoFileOpened : public std::exception
{
    const char *what() const throw()
    {
        return "No file is opened now.";
    }
};

class InvalidOpenFunc : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid arguments for open(), correct usage: open [path]";
    }
};

class InvalidNewFunc : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid arguments for new(), correct usage: new [width] [height] [fillColor]";
    }
};

class InvalidSaveAsFunc : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid arguments for saveas(), correct usage: saveas [path]";
    }
};

class InvalidCropFunc : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid arguments for crop(), correct usage: crop [point1 x] [point1 y] [point2 x] [point2 y]";
    }
};

class InvalidResizeFunc : public std::exception
{
    const char *what() const throw()
    {
        return "Invalid arguments used for resize(), correct ways to use the command:\n resize [width] [height]\n resize [percentage]";
    }
};

class IncorrectPBMExtension : public std::exception
{
    const char *what() const throw()
    {
        return "You have given an incorrect extension for this type of file(P1), please use .pbm";
    }
};

class IncorrectPGMExtension : public std::exception
{
    const char *what() const throw()
    {
        return "You have given an incorrect extension for this type of file(P2), please use .pgm";
    }
};

class IncorrectPPMExtension : public std::exception
{
    const char *what() const throw()
    {
        return "You have given an incorrect extension for this type of file(P3), please use .ppm";
    }
};

class DitherComands : public std::exception
{
    const char *what() const throw()
    {
        return "Unknown dither number, please use one of the following ones:\n1: basic 1-dimensional dither\n2: Floyd-Steinberg\n3: Fake Floyd-Steinberg\n4: Jarvis, Judice, and Ninke\n5: Stucki\n6: Atkinson\n7: Burkes\n8: Sierra\n9: Two-Row Sierra\n10: Sierra Lite\n11: 4x4 Bayer matrix\n12: 8x8 Bayer matrix\n";
    }
};