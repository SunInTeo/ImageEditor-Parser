#include "../Header Files/Image.h"

ImageType Image::strToType(const std::string &typeStr)
{
    if (typeStr == "P1")
    {
        return ImageType::P1;
    }
    else if (typeStr == "P2")
    {
        return ImageType::P2;
    }
    else if (typeStr == "P3")
    {
        return ImageType::P3;
    }
    else
    {
        throw std::invalid_argument("Incorrect type.");
    }
}

std::string Image::typeToStr(const ImageType &typeStr)
{
    if (type == ImageType::P1)
    {
        return "P1";
    }
    else if (type == ImageType::P2)
    {
        return "P2";
    }
    else if (type == ImageType::P3)
    {
        return "P3";
    }
    else
    {
        throw std::invalid_argument("Incorrect type");
    }
}

void Image::readMetaData(std::ifstream &in)
{
    type = strToType(getNextParameter(in));
    width = std::stoi(getNextParameter(in));
    height = std::stoi(getNextParameter(in));
    if (type != ImageType::P1)
    {
        maxValue = std::stoi(getNextParameter(in));
    }
}

void Image::writeMetaData(std::ofstream &out)
{
    out << typeToStr(type) << std::endl;
    out << width << std::endl;
    out << height << std::endl;
    if (type != ImageType::P1)
    {
        out << maxValue << std::endl;
    }
}

void Image::readRaster(std::ifstream &in)
{
    std::string input;
    int value;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            switch (type)
            {
            case ImageType::P1:
            case ImageType::P2:
            {
                input = getNextParameter(in);
                value = std::stoi(input);

                arr->at(i, j).red = value;
                arr->at(i, j).green = value;
                arr->at(i, j).blue = value;

                break;
            }
            case ImageType::P3:
            {
                std::string redPixelString = getNextParameter(in);
                std::string greenPixelString = getNextParameter(in);
                std::string bluePixelString = getNextParameter(in);

                int redPixelVal = std::stoi(redPixelString);
                int greenPixelVal = std::stoi(greenPixelString);
                int bluePixelVal = std::stoi(bluePixelString);

                arr->at(i, j).red = redPixelVal;
                arr->at(i, j).green = greenPixelVal;
                arr->at(i, j).blue = bluePixelVal;

                break;
            }

            default:
                break;
            }
        }
    }
}
void Image::writeRaster(std::ofstream &out)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            switch (type)
            {
            case ImageType::P1:
            case ImageType::P2:
            {
                out << arr->at(i, j).red << " ";
                break;
            }
            case ImageType::P3:
            {
                out << arr->at(i, j).red << " ";
                out << arr->at(i, j).green << " ";
                out << arr->at(i, j).blue << " ";
                break;
            }

            default:
                break;
            }
        }
        out << std::endl;
    }
}

Image::~Image()
{
    delete arr;
}

Image::Image(const std::string &path)
{
    std::ifstream in(path);
    if (!in.is_open())
    {
        throw NoFileOpened();
    }

    readMetaData(in);
    arr = new Matrix<Pixel>(height, width);
    readRaster(in);

    currentPath = path;
    in.close();
}

Image::Image(int width, int height, const std::string &hexCode)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Invalid arguments.");
    }

    Pixel pixel(hexCode);

    this->type = ImageType::P3;
    this->height = height;
    this->width = width;
    this->maxValue = 255;
    arr = new Matrix<Pixel>(height, width);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            arr->at(i, j).red = pixel.red;
            arr->at(i, j).green = pixel.green;
            arr->at(i, j).blue = pixel.blue;
        }
    }
}

void Image::saveAs(const std::string &path)
{
    std::string ext = getImageExtension(path);
    
    if (type == ImageType::P1 && ext != "pbm")
    {
        throw IncorrectPBMExtension();
    }

    if (type == ImageType::P2 && ext != "pgm")
    {
        throw IncorrectPGMExtension();
    }

    if (type == ImageType::P3 && ext != "ppm")
    {
        throw IncorrectPPMExtension();
    }

    std::ofstream out(path);
    if (!out)
    {
        throw std::invalid_argument("File cannot be saved in given path.");
    }

    writeMetaData(out);
    writeRaster(out);

    currentPath = path;
    out.close();
}

void Image::save()
{
    if (currentPath[0] != '\0')
    {
        saveAs(currentPath);
    }
    else
    {
        throw std::invalid_argument("No path found, please first use SaveAs /path/");
    }
}

ImageType Image::getType() const
{
    return type;
}
int Image::getWidth() const
{
    return width;
}
int Image::getHeight() const
{
    return height;
}
int Image::getMaxValue() const
{
    return maxValue;
}