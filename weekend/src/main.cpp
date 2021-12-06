#include "header.h"
#include "ray.h"
#include "hittable.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

hit_record hit_sphere(const std::vector<sphere>& spheres, const Ray& r) 
{
	hit_record rec;
	hit_record cur_rec;
	for each (const auto& sph in spheres)
	{
		if(sph.hit(r,0,std::numeric_limits<double>().max(),cur_rec))
			if(cur_rec.t > 0 && (cur_rec.t < rec.t || rec.t < 0))
				rec = cur_rec;
	}

	return rec;
};

color ray_color(const Ray& r, const std::vector<sphere>& spheres) {
	auto rec = hit_sphere(spheres, r);
	if (rec.t > 0.0)
		return 0.5 * color(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	
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

	// Camera

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//// Test image 
	//const int width = 200;
	//const int height = 100;
	const int channels = 3;
	img_datad img(image_width * image_height);

	std::vector<sphere> spheres = { sphere(point3(0, 0, -1), 0.5),
									sphere(point3(.5, .5, -1.6), 0.25),
									sphere(point3(-0.7, 0.3, -0.8), 0.3),
									sphere(point3(2, 1, -1.8), 0.6) };

	// compute colors 
	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cout << "Progress: " << (int)(100.0f * (float)(image_height - j)/ (float)(image_height)) << "%\r";
		for (int i = 0; i < image_width; ++i)
		{

			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r, spheres);

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
