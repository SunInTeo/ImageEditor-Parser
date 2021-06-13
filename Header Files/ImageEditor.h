/** @file ImageEditor.h
 *  @brief Edits the image.
 * 
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */
#pragma once

#include "./Image.h"

/** @brief
 * Singleton class in which processing functions for editing an image are implemented.
 */
class ImageEditor
{
private:
    ImageEditor(){

    };

    /** @brief  Checks if the current pixel is closer to 0 or the 
     *          maxValue and sets it to the value it is closer to.
     */
    void checkAndChangePixelAt(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue);

    template <int rows, int columns>
    void ditherPixelsByMatrix(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue, int matrix[rows][columns], int offset, int diviser);

    /** @brief  Inspiration: https://en.wikipedia.org/wiki/Ordered_dithering.
     */
    template <int rows, int columns>
    void ditherInBlock(Matrix<Pixel> &arr, int currentRow, int currentColumn, int maxValue, int matrix[rows][columns], int offset, int diviser);

public:
    ImageEditor(const ImageEditor &) = delete;
    ImageEditor &operator=(const ImageEditor &) = delete;

    static ImageEditor &getInstance()
    {
        static ImageEditor instance;
        return instance;
    }

    /** @brief Converts an image from a color one to a grayscaled.
      *  @param m_image the image itself
     */
    void grayscale(Image &m_image);
    /** @brief  Resizes an image using the formula from the URL in the document about our projects.
     *  @param m_image the image itself
     *  @param userHeight wanted height
     *  @param userWidth wanted width
     */
    void resize(Image &m_image, int newHeight, int newWidth);

    /** @brief  Resizes the image calling the previous resize function.
     *  @param m_image the image itself
     *  @param percentage to what percentage it is resized
     */
    void resize(Image &m_image, double percentage);

    /** @brief  Crops a rectangle from the image.
     *          Throws an exception if the arguments are incorrect/or out of bounds.
     * @param m_image the image itself
     * @param lx x coordinate of the left point
     * @param ly y coordinate of the left point
     * @param rx x coordinate of the right point
     * @param ry y coordinate of the right point
     */
    void crop(Image &m_image, int lx, int ly, int rx, int ry);

    /** @brief  The first dithering methods use their own matrixes to spread the error.
     *  The function goes thrpugh every single pixel of the image uses the template function ditherPixelsByMatrix
     *  giving it different arguments depending on the type of dithering and spreads the error to the pixels in the image accordingly.
     */
    ///@{
    void dither1D(Image &m_image);
    void ditherFloyd(Image &m_image);
    void ditherFakeFloyd(Image &m_image);
    void ditherJJN(Image &m_image);
    void ditherStucki(Image &m_image);
    void ditherAtkinson(Image &m_image);
    void ditherBurkes(Image &m_image);
    void ditherSierra(Image &m_image);
    void ditherSierraTwoRow(Image &m_image);
    void ditherSierraLite(Image &m_image);
    ///@}

    /** @brief
     *  The Bayer matrix dithering methods have an n by m coefficent matrix that is declared in their function.
     *  The function goes through the image's matrix of pixels by every n-th row and m-th column by calling the
     *  template function ditherInBlock and giving it the correct arguments.
     */
    ///@{
    void dither4x4(Image &m_image);
    void dither8x8(Image &m_image);
    ///@}
};
