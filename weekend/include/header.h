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

// Returns a random real in [0,1).
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Returns a random real in [min,max).
inline double random_double(const double& min, const double& max) {
    return min + (max - min) * random_double();
}

inline vec3 random_vec()
{
    return { random_double(),random_double() ,random_double() };
}

inline vec3 random_vec(const double& min, const double& max)
{
    return { random_double(min,max),random_double(min,max) ,random_double(min,max) };
}

inline vec3 random_vec_in_unit_sphere(uint16_t tries = 100)
{
    uint16_t counter = 0;
    while (counter < tries)
    {
        auto p = random_vec(-1, 1);
        if (p.squaredNorm() >= 1)
        {
            counter++;
            continue;
        }
        return p;
    }

    return vec3::Zero();
}

inline vec3 random_unit_vector() {
    return random_vec_in_unit_sphere().normalized();
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * v.dot(n) * n;
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