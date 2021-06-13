/** @file Image.h
 *  @brief Stores data from image.
 * 
 *  @author Teodor Karushkov
 *  @bug No known bugs.
 */

#pragma once

#include "Utils.h"
#include "Matrix.h"
#include "Pixel.h"
#include "ImageType.h"
#include "Exceptions.h"

class ImageEditor;

class Image
{
private:
    std::string currentPath;
    ImageType type;
    int width;
    int height;
    int maxValue = 1;
    Matrix<Pixel> *arr;

    /** @brief  Gets a string and return the type of image corresponding to it.
     *  @param typeStr string
     *  @return the type of image
     */
    ImageType strToType(const std::string &typeStr);

    /** @brief  Gets a type and returns it in string.
     *  @param type image type
     *  @return the type in string format
     */
    std::string typeToStr(const ImageType &type);

    /** @name   Readers and writers
     *  @brief  4 functions used to read and write both the Metadata
     *          and the raster of the image.
     */
    ///@{
    void readMetaData(std::ifstream &in);
    void readRaster(std::ifstream &in);
    void writeMetaData(std::ofstream &out);
    void writeRaster(std::ofstream &out);
    ///@}

public:
    Image() = delete;
    /** @brief  Deletes the array of pixels and frees memory.
     */
    ~Image();

    /** @brief  Opens the image at the given location.
     *          Throws an exception if it cannot acccess the file.
     *          Reads the Metadata of the image and creates a new Matrix of type Pixel with the read width and height.
     *          Then fills the array with the data read from the raster of the image.
     *  @param path string to a path
     */
    Image(const std::string &path);

    /** @brief  Throws an exception if the arguments are incorrect.  
     *          Creates a new Image and fills its data with values from the arguments.
     *  @param width    width of image
     *  @param height   height of image
     *  @param hexCode  filler value
     */
    Image(int width, int height, const std::string &hexCode);

    /** @brief  Checks if the given path has a right extension.
     *          Then writes the date to the given file. 
     *          Sets currentPath to the path it has been given.
     *          Throws an exception if the extension is incorrect/missing.
     *  @param path string to a path
     *  @return Void.
     */
    void saveAs(const std::string &path);

    /** @brief  Calls the saveAs function with current path.
     *          Throws an exception if current path is non existent. 
     *  @return Void.
     */
    void save();

    /** @name   Getters
     *  @brief  4 functions used to access the class private members.
     */
    ///@{
    ImageType getType() const;
    int getWidth() const;
    int getHeight() const;
    int getMaxValue() const;
    ///@}

    friend class ImageEditor;
};
