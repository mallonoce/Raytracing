#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <filesystem>

#include <Eigen/Dense>

using pixel = Eigen::Matrix<uint8_t, 3, 1>;
using pixelf = Eigen::Vector3f;

using img_data = std::vector<pixel>;
using img_dataf = std::vector<pixelf>;

int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_data& img);
int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_data& img, int quality = 100);
int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_dataf& img);
int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_dataf& img, int quality = 100);
#endif // _HEADER_H_