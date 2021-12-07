#include "header.h"
#include "camera.h"
#include "hittable.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;



color ray_color(const Ray& r, const hittable_list& world, int depth) 
{
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		point3 target = rec.p + rec.normal + random_unit_vector();
		return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth - 1);
	}

	auto t = 0.5 * (r.direction().y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
	// create output dir
	fs::path curDir = std::filesystem::current_path();
	curDir.append("output");
	fs::create_directory(curDir);
	std::cout << "Output Directory = " << curDir << std::endl;


	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const double samples_per_pixel_d = (double)samples_per_pixel;
	const int max_depth = 3;
	double gamma = 2.0;
	double gamma_inv = 1.0/gamma;


	// Camera
	Camera cam;
	
	//// Test image 
	const int channels = 3;
	img_datad img(image_width * image_height);

	// World
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));


	// compute colors 
	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cout << "Progress: " << (int)(100.0f * (float)(image_height - j)/ (float)(image_height)) << "%\r";
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color = color::Zero();
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = double(i + random_double(-1, 1)) / (image_width - 1);
				auto v = double(j + random_double(-1, 1)) / (image_height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			
			// antialiasing
			pixel_color /= samples_per_pixel_d;
			// gamma correction 
			pixel_color[0] = std::pow(pixel_color[0], gamma_inv);
			pixel_color[1] = std::pow(pixel_color[1], gamma_inv);
			pixel_color[2] = std::pow(pixel_color[2], gamma_inv);

			// write to memory
			img[index] = 255.99 * pixel_color;
			index++;
		}
	}
	std::cout << "\nDone.\n";
	
	// save images
	save_image_png((curDir / fs::path("my_stbpng_col.png")).string().c_str(), image_width, image_height, channels, img);
	//save_image_jpg((curDir / fs::path("my_stbjpg_col.jpg")).string().c_str(), image_width, image_height, img, 100);

	return 0;
}
