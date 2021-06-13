/** @file CommandHandler.h
 *  @brief Handles the user's input.
 * 
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */
#pragma once

#include "./Command.h"
#include "./ImageEditor.h"
#include "./Exceptions.h"

const int OPEN_CMD_SIZE = 2;
const int NEW_CMD_SIZE = 4;
const int SAVEAS_CMD_SIZE = 2;
const int SAVE_CMD_SIZE = 1;
const int CROP_CMD_SIZE = 5;
const int RESIZE_WITH_PARAMETERS_CMD_SIZE = 3;
const int RESIZE_PERCENTAGE_CMD_SIZE = 2;
const int DITHER_CMD_SIZE = 2;

class CommandHandler
{
private:
    Image *m_image;
    bool isImageOpened = false;

    /** @brief When called excutes the different commands it is given.
     *  @param cmd command which the user has given
     *  @retval TRUE if user continues to give commands.
     *  @retval FALSE if user types EXIT
     */
    bool executeCommand(const Command &cmd);

public:
    CommandHandler();

    /** @brief Loads an image from the given path.
     *  @param path string including the path where the image is 
     */
    CommandHandler(std::string path);
    ~CommandHandler();

    /** @brief When called starts the process of reading commands.
     * The function reads a line from the console and puts it in a variable from type Command.
     * Which gets split into different strings.
     * After that executeCommand() is called and the process of performing commands continues until the user types "STOP".
     *  @return Void.
     */
    void startReading();
};
