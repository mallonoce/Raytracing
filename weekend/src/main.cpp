#include "header.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	// create output dir
	fs::path curDir = std::filesystem::current_path();
	curDir.append("output");
	fs::create_directory(curDir);
	std::cout << "Output Directory = " << curDir << std::endl;


	// Test image 
	const int width = 200;
	const int height = 100;
	const int channels = 3;
	img_dataf img(width * height);

	// compute colors 
	int index = 0;
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			img[index][0] = 255.99f * (float)i / (float)width;
			img[index][1] = 255.99f * (float)j / (float)height;
			img[index][2] = 255.99f * 0.2f;
			index++;
		}
	}

	// save images
	save_image_png((curDir / fs::path("my_stbpng.png")).string().c_str(), width, height, channels, img);
	save_image_jpg((curDir / fs::path("my_stbjpg3.jpg")).string().c_str(), width, height, img, 100);

	return 0;
}
