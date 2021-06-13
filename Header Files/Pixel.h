/** @file Exceptions.h
 *  @brief
 * 
 *  Structure Pixel consisting of three int: red, green and blue.
 *  Storage for the data(values) for pixels;
 *
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */

#pragma once

#include <cmath>
#include <string>
#include <stdexcept>

const char HEX_CODE_START_SYMBOL = '#';
const int HEX_CODE_LENGTH = 7;

struct Pixel
{
    int red;
    int green;
    int blue;

    /** @brief 
     *  Sets all the values to 0
     *  By default it is a black pixel;
     */
    Pixel();

    /** @brief 
     *  Sets all the values to the given ones
     *  
     *  @param red
     *  @param green
     *  @param blue
     */
    Pixel(int red, int green, int blue);

    /** @brief
     *  Creates a pixel from a given hex code,
     *  if the hex code is incorrectthrows an exception.
     *  @param hexCode string of a hex code
     */
    Pixel(std::string hexCode);

private:
    /** @brief
     *  Receives a hex code and converts it to int.
     *  It assumes that the given code is correct.
     *  @param hexCode string of a hex code
     *  @return Int value corresponding to the hex one.
     */
    int hexToDecimal(std::string hexCode);

	/// The next two functions are currently out of order.

    /** @brief
     *  Receives a character and checks if it is a valid character for a hex code.
     *  @param ch symbol
     *  @return True/False depending on the result.
     */
    bool isValidHexSymbol(const char ch);

    /** @brief
     *  Receives a hex code and checks if it is correct.
     *  @param str string of a hex code
     *  @return True/False depending on the result.
     */
    bool isValidHexadecimalNumber(const std::string &str);
};
