#include "errors.h"
#include <cstdlib>

// Prints out an error messsage and exits the game
void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Press a key to quit";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(420);
}