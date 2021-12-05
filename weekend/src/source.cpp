#include "header.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_data& img)
{
	// if CHANNEL_NUM is 4, you can use alpha channel in png
	return stbi_write_png(p.string().c_str(), w, h, channels, img.data(), w * channels);
}

int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_data& img, int quality)
{
	// You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
	return stbi_write_jpg(p.string().c_str(), w, h, 3, img.data(), quality);
}

int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_dataf& img)
{
	img_data img_conv(img.size());

	for (int i = 0; i < img.size(); i++)
		img_conv[i] = pixel(static_cast<uint8_t>(img[i].x()), static_cast<uint8_t>(img[i].y()), static_cast<uint8_t>(img[i].z())); //img[i].cast<pixel>();

	// if channels is 4, you can use alpha channel in png
	return save_image_png(p, w, h, channels, img_conv);
	 stbi_write_png(p.string().c_str(), w, h, channels, img_conv.data(), w * channels);
}

int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_dataf& img, int quality)
{
	img_data img_conv(img.size());

	for (int i = 0; i < img.size(); i++)
		img_conv[i] = pixel(static_cast<uint8_t>(img[i].x()), static_cast<uint8_t>(img[i].y()), static_cast<uint8_t>(img[i].z())); //img[i].cast<pixel>();

	// You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
	return save_image_jpg(p, w, h, img_conv, quality);
}