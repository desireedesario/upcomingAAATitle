#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "errors.h"

GLTexture ImageLoader::loadPNG(std::string, filePath) {
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;
	
	if (IOManager::readFileToBuffer(filePath, in) == false) {
		fatalError("Failed to load PNG file to budder");
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0) {
		fatalError("DecodePNG failed with error: " + std::to_string(errorCode));
	}

	//generate the texture obj
}