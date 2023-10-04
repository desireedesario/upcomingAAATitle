//a non-standard but widely supported preprocessor directive designed to cause the current source file to be included only once in a single compilation.
#pragma once

#include <vector>
#include <string>

class IOManager
{
// making a static class (only using once) because we only need one IOManager for reading and writing files
public:
	//buffer is just another name for array
	//using a ventor of char
	// ue & to fill in your own buffer
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};
