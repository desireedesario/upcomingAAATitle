#include "IOManager.h"
#include <fstream>

// a vector is just a wrapper around an array
bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	// read in binary format
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//read the entire contents into the buffer
	//need to determine how big a file is
	// 
	//seek to the end
	//seekg will read the file and place the cursor right at the end
	file.seekg(0, std::ios::end);

	//Get file size
	// tells us how many bytes are in the current location
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//ASK this probably doesnt matter. is this needed? 
	// reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	// get the first element of buffer using the pointer of the c string
	// pretending its a buffer of char
	file.read((char *) & (buffer[0]), fileSize);
	file.close();

	return true;
}