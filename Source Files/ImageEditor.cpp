#include "../Header Files/ImageEditor.h"

void ImageEditor::checkAndChangePixelAt(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue)
{
    if (arr.at(currentRow, currentColumn).red <= maxValue / 2)
    {
        arr.at(currentRow, currentColumn).red = 0;
    }
    else
    {
        arr.at(currentRow, currentColumn).red = maxValue;
    }

    if (arr.at(currentRow, currentColumn).green <= maxValue / 2)
    {
        arr.at(currentRow, currentColumn).green = 0;
    }
    else
    {
        arr.at(currentRow, currentColumn).green = maxValue;
    }

    if (arr.at(currentRow, currentColumn).blue <= maxValue / 2)
    {
        arr.at(currentRow, currentColumn).blue = 0;
    }
    else
    {
        arr.at(currentRow, currentColumn).blue = (int)maxValue;
    }
}

template <int rows, int columns>
void ImageEditor::ditherPixelsByMatrix(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue, int matrix[rows][columns], int offset, int diviser)
{

    for (int i = 0; i < rows; ++i)
    {
        for (int j = (i == 0) ? offset + 1 : 0; j < columns; ++j)
        {
            if (currentRow + i < arr.getRows() && currentRow + i >= 0 && currentColumn + j - offset < arr.getColumns() && currentColumn + j - offset >= 0)
            {
                if (arr.at(currentRow, currentColumn).red <= maxValue / 2)
                {
                    arr.at(currentRow + i, currentColumn + j - offset).red += (double)arr.at(currentRow, currentColumn).red / diviser * matrix[i][j];
                }
                else
                {
                    arr.at(currentRow + i, currentColumn + j - offset).red += ((double)arr.at(currentRow, currentColumn).red - (double)maxValue) / diviser * matrix[i][j];
                }

                if (arr.at(currentRow, currentColumn).green <= maxValue / 2)
                {
                    arr.at(currentRow + i, currentColumn + j - offset).green += (double)arr.at(currentRow, currentColumn).green / diviser * matrix[i][j];
                }
                else
                {
                    arr.at(currentRow + i, currentColumn + j - offset).green += ((double)arr.at(currentRow, currentColumn).green - (double)maxValue) / diviser * matrix[i][j];
                }

                if (arr.at(currentRow, currentColumn).blue <= maxValue / 2)
                {
                    arr.at(currentRow + i, currentColumn + j - offset).blue += (double)arr.at(currentRow, currentColumn).blue / diviser * matrix[i][j];
                }
                else
                {
                    arr.at(currentRow + i, currentColumn + j - offset).blue += ((double)arr.at(currentRow, currentColumn).blue - (double)maxValue) / diviser * matrix[i][j];
                }
            }
        }
    }
}

template <int rows, int columns>
void ImageEditor::ditherInBlock(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue, int matrix[rows][columns], int offset, int diviser)
{

    for (int i = 0; i < rows; ++i)
    {
        for (int j = (i == 0) ? offset + 1 : 0; j < columns; ++j)
        {
            if (currentRow + i < arr.getRows() && currentRow + i >= 0 && currentColumn + j - offset < arr.getColumns() && currentColumn + j - offset >= 0)
            {
                arr.at(currentRow + i, currentColumn + j - offset).red = arr.at(currentRow + i, currentColumn + j - offset).red + (int)((double)maxValue * ((double)matrix[i][j] / (double)diviser - 0.5));
                arr.at(currentRow + i, currentColumn + j - offset).green = arr.at(currentRow + i, currentColumn + j - offset).green + (int)((double)maxValue * ((double)matrix[i][j] / (double)diviser - 0.5));
                arr.at(currentRow + i, currentColumn + j - offset).blue = arr.at(currentRow + i, currentColumn + j - offset).blue + (int)((double)maxValue * ((double)matrix[i][j] / (double)diviser - 0.5));

                checkAndChangePixelAt(arr, currentRow + i, currentColumn + j - offset, maxValue);
            }
        }
    }
}

void ImageEditor::resize(Image &m_image, int userHeight, int userWidth)
{

    Matrix<Pixel> *newArr = new Matrix<Pixel>(userHeight, userWidth);

    try
    {
        for (int i = 0; i < userHeight; ++i)
        {
            for (int j = 0; j < userWidth; ++j)
            {

                int newHeight = (int)round((double)i / (double)userHeight * (double)m_image.height);
                int newWidth = (int)round((double)j / (double)userWidth * (double)m_image.width);

                if (newHeight > m_image.height - 1)
                {
                    newHeight = m_image.height - 1;
                }
                if (newWidth > m_image.width - 1)
                {
                    newWidth = m_image.width - 1;
                }

                newArr->at(i, j).red = m_image.arr->at(newHeight, newWidth).red;
                newArr->at(i, j).green = m_image.arr->at(newHeight, newWidth).green;
                newArr->at(i, j).blue = m_image.arr->at(newHeight, newWidth).blue;
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Something happened while editing the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
    m_image.height = userHeight;
    m_image.width = userWidth;
}
void ImageEditor::resize(Image &m_image, double percentage)
{
    resize(m_image, (int)((double)m_image.height * percentage / 100), (int)((double)m_image.width * percentage / 100));
}

void ImageEditor::crop(Image &m_image, int lx, int ly, int rx, int ry)
{

    int trueLy = std::min(ly, ry);
    int trueLx = std::min(lx, rx);
    int trueRy = std::max(ly, ry);
    int trueRx = std::max(lx, rx);

    if (trueLx >= m_image.width || trueLy >= m_image.height)
    {
        throw std::invalid_argument("Dimensions exceed the image's possibilities");
    }

    int endX = std::min(trueRx, m_image.width);
    int endY = std::min(trueRy, m_image.height);

    int userHeight = endY - trueLy;
    int userWidth = endX - trueLx;

    Matrix<Pixel> *newArr = new Matrix<Pixel>(userHeight, userWidth);

    try
    {
        for (int i = 0; i < userHeight; ++i)
        {
            for (int j = 0; j < userWidth; ++j)
            {
                if (i + trueLy < m_image.height && i + trueLy >= 0 && j + trueLx < m_image.width && j + trueLx >= 0)
                {
                    newArr->at(i, j) = m_image.arr->at(i + trueLy, j + trueLx);
                }
                else
                {
                    delete newArr;
                    throw std::invalid_argument("Something happened while cropping the image.");
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Something happened while cropping the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
    m_image.height = userHeight;
    m_image.width = userWidth;
}

void ImageEditor::grayscale(Image &m_image)
{
    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);
    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                int color = newArr->at(i, j).red * 0.21 + newArr->at(i, j).green * 0.72 + newArr->at(i, j).blue * 0.07;
                newArr->at(i, j).red = color;
                newArr->at(i, j).green = color;
                newArr->at(i, j).blue = color;
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Something happened while grayscaling the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::dither1D(Image &m_image)
{
    int mat[1][2] = {
        0, 1};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<1, 2>(*newArr, i, j, m_image.maxValue, mat, 0, 1);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherFloyd(Image &m_image)
{

    int mat[2][3] = {
        0, 0, 7,
        3, 5, 1};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<2, 3>(*newArr, i, j, m_image.maxValue, mat, 1, 16);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherFakeFloyd(Image &m_image)
{
    int mat[2][2] = {
        0,
        3,
        3,
        2,
    };

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<2, 2>(*newArr, i, j, m_image.maxValue, mat, 0, 8);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherJJN(Image &m_image)
{
    int mat[3][5] = {
        0, 0, 0, 7, 5,
        3, 5, 7, 5, 3,
        1, 3, 5, 3, 1};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<3, 5>(*newArr, i, j, m_image.maxValue, mat, 2, 48);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherStucki(Image &m_image)
{
    int mat[3][5] = {
        0, 0, 0, 8, 4,
        2, 4, 8, 4, 2,
        1, 2, 4, 2, 1};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<3, 5>(*newArr, i, j, m_image.maxValue, mat, 2, 42);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherAtkinson(Image &m_image)
{
    int mat[3][4] = {
        0, 0, 1, 1,
        1, 1, 1, 0,
        0, 1, 0, 0};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<3, 4>(*newArr, i, j, m_image.maxValue, mat, 1, 8);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherBurkes(Image &m_image)
{
    int mat[2][5] = {
        0, 0, 0, 8, 4,
        2, 4, 8, 4, 2};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<2, 5>(*newArr, i, j, m_image.maxValue, mat, 2, 32);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherSierra(Image &m_image)
{
    int mat[3][5] = {
        0, 0, 0, 5, 3,
        2, 4, 5, 4, 2,
        0, 2, 3, 2, 0};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<3, 5>(*newArr, i, j, m_image.maxValue, mat, 2, 32);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherSierraTwoRow(Image &m_image)
{
    int mat[2][5] = {
        0,
        0,
        0,
        4,
        3,
        1,
        2,
        3,
        2,
        1,
    };

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<2, 5>(*newArr, i, j, m_image.maxValue, mat, 2, 16);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::ditherSierraLite(Image &m_image)
{
    int mat[2][3] = {
        0, 0, 2,
        1, 1, 0};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                ditherPixelsByMatrix<2, 3>(*newArr, i, j, m_image.maxValue, mat, 1, 4);
                checkAndChangePixelAt(*newArr, i, j, m_image.maxValue);
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::dither4x4(Image &m_image)
{
    int mat[4][4] = {
        0, 8, 2, 10,
        12, 4, 14, 6,
        3, 11, 1, 9,
        15, 7, 13, 5};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                if (i % 4 == 0 && j % 4 == 0)
                {
                    ditherInBlock<4, 4>(*newArr, i, j, m_image.maxValue, mat, -1, 16);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}

void ImageEditor::dither8x8(Image &m_image)
{
    int mat[8][8] = {
        0, 32, 8, 40, 2, 34, 10, 42,
        48, 16, 56, 24, 50, 18, 58, 26,
        12, 44, 4, 36, 14, 46, 6, 38,
        60, 28, 52, 20, 62, 30, 54, 22,
        3, 35, 11, 43, 1, 33, 9, 41,
        51, 19, 59, 27, 49, 17, 57, 25,
        15, 47, 7, 39, 13, 45, 5, 37,
        63, 31, 55, 23, 61, 29, 53, 21};

    Matrix<Pixel> *newArr = new Matrix<Pixel>(*m_image.arr);

    try
    {
        for (int i = 0; i < m_image.height; ++i)
        {
            for (int j = 0; j < m_image.width; ++j)
            {
                if (i % 8 == 0 && j % 8 == 0)
                {
                    ditherInBlock<8, 8>(*newArr, i, j, m_image.maxValue, mat, -1, 64);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        delete newArr;
        throw std::invalid_argument("Error, couldn't dither the image.");
    }

    delete m_image.arr;
    m_image.arr = newArr;
}
