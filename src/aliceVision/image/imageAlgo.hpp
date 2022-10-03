#pragma once

#include <string>

#include <aliceVision/image/io.hpp>

#include <OpenImageIO/paramlist.h>
#include <OpenImageIO/imagebufalgo_util.h>


namespace oiio = OIIO;

namespace aliceVision
{

class rgb;
template<typename Color> class LegacyImage;


namespace imageAlgo
{

void RGBtoXYZ(oiio::ImageBuf::Iterator<float>& pixel);
void XYZtoRGB(oiio::ImageBuf::Iterator<float>& pixel);

void XYZtoLAB(oiio::ImageBuf::Iterator<float>& pixel);
void LABtoXYZ(oiio::ImageBuf::Iterator<float>& pixel);

void RGBtoLAB(oiio::ImageBuf::Iterator<float>& pixel);
void LABtoRGB(oiio::ImageBuf::Iterator<float>& pixel);

/**
 * @brief split an image in chunks and proces them in parallel
 * @param [in] image to process (in place or not)
 * @param [in] pixelFunc the function to apply
 */
void processImage(oiio::ImageBuf& image, std::function<void(oiio::ImageBuf::Iterator<float>&)> pixelFunc);
void processImage(oiio::ImageBuf& dst, const oiio::ImageBuf& src, std::function<void(oiio::ImageBuf::Iterator<float>&)> pixelFunc);

void colorconvert(oiio::ImageBuf& image, const std::string& fromColorSpaceOIIOName,
                  image::EImageColorSpace toColorSpace);
void colorconvert(oiio::ImageBuf& image, image::EImageColorSpace fromColorSpace,
                  image::EImageColorSpace toColorSpace);
void colorconvert(ImageRGBAf& image, image::EImageColorSpace fromColorSpace,
                  image::EImageColorSpace toColorSpace);
void colorconvert(image::Image<image::RGBfColor>& image, image::EImageColorSpace fromColorSpace,
                  image::EImageColorSpace toColorSpace);
void colorconvert(image::Image<image::RGBAfColor>& image, image::EImageColorSpace fromColorSpace,
                  image::EImageColorSpace toColorSpace);
void colorconvert(oiio::ImageBuf& dst, const oiio::ImageBuf& src,
                  image::EImageColorSpace fromColorSpace, image::EImageColorSpace toColorSpace);

/**
 * @brief transpose a given image buffer
 * @param[in] width The image buffer width
 * @param[in] height The image buffer height
 * @param[in,out] buffer The image buffer
 */
void transposeImage(int width, int height, std::vector<unsigned char>& buffer);
void transposeImage(int width, int height, std::vector<rgb>& buffer);
void transposeImage(int width, int height, std::vector<float>& buffer);
void transposeImage(int width, int height, std::vector<image::RGBfColor>& buffer);

/**
 * @brief resize a given image buffer
 * @param[in] inWidth The input image buffer width
 * @param[in] inHeight The input image buffer height
 * @param[in] downscale The resize downscale
 * @param[in] inBuffer The input image buffer
 * @param[out] outBuffer The output image buffer
 * @param[in] filter The name of a high-quality filter to use when resampling
 *            Default is bilinear resampling
 *            See openImageIO documentation "ImageBufAlgo filtername"
 * @param[in] filterSize The resize filter size
 */
void resizeImage(int inWidth, int inHeight, int downscale, const std::vector<unsigned char>& inBuffer, std::vector<unsigned char>& outBuffer, const std::string& filter = "", float filterSize = 0);
void resizeImage(int inWidth, int inHeight, int downscale, const std::vector<rgb>& inBuffer, std::vector<rgb>& outBuffer, const std::string& filter = "", float filterSize = 0);
void resizeImage(int inWidth, int inHeight, int downscale, const std::vector<float>& inBuffer, std::vector<float>& outBuffer, const std::string& filter = "", float filterSize = 0);
void resizeImage(int inWidth, int inHeight, int downscale,
                 const std::vector<image::RGBfColor>& inBuffer,
                 std::vector<image::RGBfColor>& outBuffer,
                 const std::string& filter = "", float filterSize = 0);
void resizeImage(int downscale, const ImageRGBAf& inImage, ImageRGBAf& outImage, const std::string& filter = "", float filterSize = 0);
void resizeImage(int downscale, const image::Image<image::RGBfColor>& inImage,
                 image::Image<image::RGBfColor>& outImage,
                 const std::string& filter = "", float filterSize = 0);
void resizeImage(int downscale, const image::Image<image::RGBAfColor>& inImage,
                 image::Image<image::RGBAfColor>& outImage,
                 const std::string& filter = "", float filterSize = 0);

/**
 * @brief convolve a given image buffer
 * @param[in] inWidth The input image buffer width
 * @param[in] inHeight The input image buffer heightt
 * @param[in] inBuffer The input image buffer
 * @param[out] outBuffer outBuffer The output image buffer
 * @param[in] kernel The kernel name, can be "gaussian", "sharp-gaussian", "box", ...
 *            Default is gaussian kernel
 *            See openImageIO documentation "ImageBufAlgo.make_kernel"
 * @param[in] kernelWidth The kernel width
 * @param[in] kernelHeight The kernal height
 */
void convolveImage(int inWidth, int inHeight, const std::vector<unsigned char>& inBuffer, std::vector<unsigned char>& outBuffer, const std::string& kernel = "gaussian", float kernelWidth = 5.0f, float kernelHeight = 5.0f);
void convolveImage(int inWidth, int inHeight, const std::vector<rgb>& inBuffer, std::vector<rgb>& outBuffer, const std::string& kernel = "gaussian", float kernelWidth = 5.0f, float kernelHeight = 5.0f);
void convolveImage(int inWidth, int inHeight, const std::vector<float>& inBuffer, std::vector<float>& outBuffer, const std::string& kernel = "gaussian", float kernelWidth = 5.0f, float kernelHeight = 5.0f);
void convolveImage(int inWidth, int inHeight, const std::vector<image::RGBfColor>& inBuffer,
                   std::vector<image::RGBfColor>& outBuffer,
                   const std::string& kernel = "gaussian",
                   float kernelWidth = 5.0f, float kernelHeight = 5.0f);

/**
 * @brief fill holes in a given image buffer with plausible values
 * @param[in] inWidth The input image buffer width
 * @param[in] inHeight The input image buffer height
 * @param[in,out] colorBuffer The image buffer to fill
 * @param[in] alphaBuffer The input alpha buffer containing 0.0/1.0 for empty/valid pixels
 */
void fillHoles(int inWidth, int inHeight, std::vector<image::RGBfColor>& colorBuffer,
               const std::vector<float>& alphaBuffer);
void fillHoles(image::Image<image::RGBfColor>& image, const std::vector<float>& alphaBuffer);


}
}
