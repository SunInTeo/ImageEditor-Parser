/** @file Matrix.h
 *  @brief 
 *  
 *  Template class that creates and manages an n by m matrix of whatever class is given to it as a template.
 *  Container for the pixels of the image.
 *
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */

#pragma once

#include <iostream>

template <class T>
class Matrix
{
private:
    T **matrix;
    int rows = 0;
    int columns = 0;

    void releaseByRows(int rows);
    void allocate();
    void copy(const Matrix &other);

public:
    Matrix(int rows, int columns);
    ~Matrix();
    Matrix<T> &operator=(const Matrix<T> &other);
    Matrix(const Matrix<T> &other);

    T &at(int i, int j);
    const T &at(int i, int j) const;

    int getRows() const;
    int getColumns() const;
};

template <class T>
void Matrix<T>::releaseByRows(int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template <class T>
void Matrix<T>::allocate()
{
    matrix = new T *[rows];
    if (!matrix)
    {
        throw std::invalid_argument("No available memory.");
    }

    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new T[columns];
        if (!matrix[i])
        {
            releaseByRows(i);
        }
    }
}

template <class T>
void Matrix<T>::copy(const Matrix<T> &other)
{
    if (!(rows == 0 || columns == 0))
    {
        releaseByRows(rows);
    }

    rows = other.rows;
    columns = other.columns;

    allocate();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = other.at(i, j);
        }
    }
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this;
}
template <class T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    copy(other);
}

template <class T>
Matrix<T>::Matrix(int rows, int columns)
{
    if (rows <= 0 || columns <= 0)
    {
        throw std::invalid_argument("Incorrect width and/or height.");
    }

    this->rows = rows;
    this->columns = columns;
    allocate();
}

template <class T>
Matrix<T>::~Matrix()
{
    releaseByRows(rows);
}

template <class T>
T &Matrix<T>::at(int i, int j)
{
    return matrix[i][j];
}

template <class T>
const T &Matrix<T>::at(int i, int j) const
{
    return matrix[i][j];
}

template <class T>
int Matrix<T>::getRows() const
{
    return rows;
}

template <class T>
int Matrix<T>::getColumns() const
{
    return columns;
}