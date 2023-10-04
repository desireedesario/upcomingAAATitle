#pragma once
#include <vector>

// std::vector<unsigned char>& out_image is a char is rgba values
// unsigned long& image_width, unsigned long& image_height he dimensions of the image
// const unsigned char* in_png the actual png data OR pointer to the buffer of the PNG file in memory
extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);