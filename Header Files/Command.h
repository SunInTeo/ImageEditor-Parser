/** @file Command.h
 *  @brief 
 * 
 *  Class Command helps with processing given commands.
 * 
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

class Command
{
private:
    std::string rawString;
    std::vector<std::string> arrString;

public:
    /** @brief Constructor. Receives a raw string of commands and
     *                      divides them into different ones and
     *                      puts them in a container(the vector of commands).
     *  @param string raw string which is parsed into different commands 
     */
    Command(std::string);

    /** @brief When called returns the raw string that was first handed.
     *  @return the original string passed to the constructor
     */
    std::string getCommand();
    /** @brief When called returns the size of the vector(the container).
     *  @return int value
     */
    int getSize() const;

    /** @brief Prints commands.
     *         Used in unite tests only.  
     *  @return Void.
     */
    void print();

    /** @brief Returns the string that is at the given position in the vector.  
     * 
     *  @param pos the position of the command we are looking for 
     *  @return command as a string
     */
    std::string &operator[](size_t pos);
    /** @brief Returns the string that is at the given position in the vector.
     *         But wurks for const. 
     *  @param pos the position of the command we are looking for 
     *  @return command as a string
     */
    const std::string &operator[](size_t pos) const;
};
