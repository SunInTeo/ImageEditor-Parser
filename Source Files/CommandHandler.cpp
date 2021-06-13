#include "../Header Files/CommandHandler.h"

CommandHandler::CommandHandler()
{
}

CommandHandler::CommandHandler(std::string path)
{
    try
    {
        m_image = new Image(path);
        isImageOpened = true;
    }
    catch (const std::exception &e)
    {
        isImageOpened = false;
        std::cout << e.what() << "\n";
    }
}

CommandHandler::~CommandHandler()
{
    if (isImageOpened)
    {
        delete m_image;
    }
}

void CommandHandler::startReading()
{
    std::string input;
    bool keepReading = true;
    do
    {
        getline(std::cin, input);
        Command currentCmd(input);
        keepReading = executeCommand(currentCmd);

    } while (keepReading);
}

bool CommandHandler::executeCommand(const Command &cmd)
{
    std::string firstArg = toUpper(cmd[0]);

    if (firstArg == "EXIT")
    {
        try
        {
            if (isImageOpened)
            {
                delete m_image;
                isImageOpened = false;
            }
            std::cout << "End of program\n";
            return false;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    if (firstArg == "CLOSE")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }

            std::cout << "Are you sure you want to close the current file?\n";
            std::string response;
            getline(std::cin, response);
            Command responseCmd(response);

            if (toUpper(responseCmd[0]) == "YES" || toUpper(responseCmd[0]) == "Y")
            {
                delete m_image;
                isImageOpened = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "OPEN")
    {
        try
        {
            if (isImageOpened)
            {
                std::cout << "Are you sure you want to close the current file?\n";
                std::string response;
                getline(std::cin, response);
                Command responseCmd(response);

                if (toUpper(responseCmd[0]) == "YES" || toUpper(responseCmd[0]) == "Y")
                {
                    delete m_image;
                    if (cmd.getSize() != OPEN_CMD_SIZE)
                    {
                        throw InvalidOpenFunc();
                    }

                    m_image = new Image(cmd[1]);
                    isImageOpened = true;
                }
            }
            else
            {
                if (cmd.getSize() != OPEN_CMD_SIZE)
                {
                    throw InvalidOpenFunc();
                }

                m_image = new Image(cmd[1]);
                isImageOpened = true;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "NEW")
    {
        try
        {
            if (isImageOpened)
            {
                Command closeCmd("CLOSE");
                executeCommand(toUpper(cmd[0]));
            }
            if (cmd.getSize() != NEW_CMD_SIZE)
            {
                throw InvalidNewFunc();
            }

            m_image = new Image(std::stoi(cmd[1]), std::stoi(cmd[2]), cmd[3]);
            isImageOpened = true;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "SAVEAS")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }
            if (cmd.getSize() != SAVEAS_CMD_SIZE)
            {
                throw InvalidSaveAsFunc();
            }

            m_image->saveAs(cmd[1]);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "SAVE")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }
            if (cmd.getSize() != SAVE_CMD_SIZE)
            {
                throw std::invalid_argument("Too many arguments");
            }

            m_image->save();
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "CROP")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }
            if (cmd.getSize() != CROP_CMD_SIZE)
            {
                throw InvalidCropFunc();
            }

            ImageEditor::getInstance().crop(*m_image, std::stoi(cmd[1]), std::stoi(cmd[2]), std::stoi(cmd[3]), std::stoi(cmd[4]));
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "RESIZE")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }
            if (cmd.getSize() == RESIZE_WITH_PARAMETERS_CMD_SIZE)
            {
                ImageEditor::getInstance().resize(*m_image, std::stoi(cmd[1]), std::stoi(cmd[2]));
            }
            else if (cmd.getSize() == RESIZE_PERCENTAGE_CMD_SIZE)
            {
                ImageEditor::getInstance().resize(*m_image, std::stoi(cmd[1]));
            }
            else
            {
                throw InvalidResizeFunc();
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else if (firstArg == "DITHER")
    {
        try
        {
            if (!isImageOpened)
            {
                throw NoFileOpened();
            }
            if (cmd.getSize() != DITHER_CMD_SIZE)
            {
                throw DitherComands();
            }

            int algorithm = std::stoi(cmd[1]);
            ImageEditor::getInstance().grayscale(*m_image);
            switch (algorithm)
            {
            case 1:
                ImageEditor::getInstance().dither1D(*m_image);
                break;
            case 2:
                ImageEditor::getInstance().ditherFloyd(*m_image);
                break;
            case 3:
                ImageEditor::getInstance().ditherFakeFloyd(*m_image);
                break;
            case 4:
                ImageEditor::getInstance().ditherJJN(*m_image);
                break;
            case 5:
                ImageEditor::getInstance().ditherStucki(*m_image);
                break;
            case 6:
                ImageEditor::getInstance().ditherAtkinson(*m_image);
                break;
            case 7:
                ImageEditor::getInstance().ditherBurkes(*m_image);
                break;
            case 8:
                ImageEditor::getInstance().ditherSierra(*m_image);
                break;
            case 9:
                ImageEditor::getInstance().ditherSierraTwoRow(*m_image);
                break;
            case 10:
                ImageEditor::getInstance().ditherSierraLite(*m_image);
                break;
            case 11:
                ImageEditor::getInstance().dither4x4(*m_image);
                break;
            case 12:
                ImageEditor::getInstance().dither8x8(*m_image);
                break;
            default:
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    else
    {
        std::cout << "Command not recognised\n";
    }

    return true;
}