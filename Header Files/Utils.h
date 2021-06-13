/** @file Utils.h
 *  @brief Provides helper functions.
 *
 *  This contains a set of free-functions which are used 
 *  in many other parts of the project.
 *
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

const int PATH_SIZE = 5;

/** @brief Receives a string and converts it to upper case.
 *
 *  This function is used when comparing user input and available commands.
 *  This is done so we can assure that the input will be correct
 *  however the command has been typed. 
 * 
 *  @param str the string to transform
 *  @return The string in upper case 
 */
std::string toUpper(const std::string &str);

/** @brief Receives a string and a character 
 *         and checks if the string contains the given char.
 *
 *  This function is used for reading image files.
 *  It mostly helps to differentiate comments from actual info
 *  in those files. 
 * 
 *  @param str the string to transform
 *  @param c   the char we are searching for
 *  @return True/False depending on the outcome. 
 */
bool stringContains(std::string &str, char c);

/** @brief Receives a string and a character 
 *         and removes the part of the string
 *         that comes after the given charecter
 *         /and the character itself/.
 *
 *  This function is used for reading image files.
 *  Combined with the previous one /string contains()/ 
 *  helps to differentiate comments from actual info
 *  in those files. 
 * 
 *  @param str the string to transform
 *  @param c   the char we are searching for
 *  @return Nothing, just transforms the string 
 */
void trimWordsAfterGivenCharFromString(std::string &str, char c);

/** @brief Receives an std::ifstream& and uses getline to go to the file's next line.
 *  @param in std::ifstream&
 *  @return Void. 
 */
void goToNextLine(std::ifstream &in);

/** @brief Receives an std::ifstream& and returns the next parameter as a string.
 * 
 *  If the next parameter contains a '#' /start of a comment/ somwhere in the line, 
 *  it trims and returns only the parameter.
 *  If the next parameter starts with a '#', 
 *  the function goes to the next line and recursively calls itself again.
 * 
 *  @param in std::ifstream&
 *  @return String containing next parameter. 
 */
std::string getNextParameter(std::ifstream &in);

/** @brief Receives a path to a file and returns its extension.
 *  
 *  Throws an exception if path has no extension 
 *  or it is incorrect.
 *  
 *  @param path string path
 *  @return String containing the image's extension. 
 */
std::string getImageExtension(const std::string &path);