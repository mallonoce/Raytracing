#ifndef _HEADER_H_
#define _HEADER_H_

// Common Headers
#include <iostream>
#include <filesystem>
#include <cstdlib>

#include <Eigen/Dense>

using vec3 = Eigen::Vector3d;
using color = Eigen::Vector3d;
using point3 = Eigen::Vector3d;

using pixel = Eigen::Matrix<uint8_t, 3, 1>;
using pixeld = Eigen::Vector3d;

using img_data = std::vector<pixel>;
using img_datad = std::vector<pixeld>;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_data& img);
int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_data& img, int quality = 100);
int save_image_png(const std::filesystem::path& p, int w, int h, int channels, const img_datad& img);
int save_image_jpg(const std::filesystem::path& p, int w, int h, const img_datad& img, int quality = 100);
#endif // _HEADER_H_