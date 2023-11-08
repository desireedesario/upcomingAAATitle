#include "MainGame.h"
#include <iostream>
#include <string>
#include "errors.h"

// Constructor that initializes private member variables
// QUESTION FOR NATHAN (dup)
// in the tutorial ben uses this initialization list and says it is faster
// is this still necessary or is it a practice for old versions
// and with modern compilers this is something the compiler will just take care of now?
MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
	_time = 0;
	_mouseX = 0;
	_mouseY = 0;
}

// Destructor
MainGame::~MainGame()
{

}

// runs the game
void MainGame::run()
{
	initSystems();
	initShaders();

	// Initialize our sprite (temporarily) THE SIZE
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	// only returns when the game ends
	gameLoop();
}


void MainGame::initShaders()
{
	//compile shaders
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	// adding the attributes of our vertex shaders
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	// linking shaders
	_colorProgram.linkShaders();
}

// Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow(
		"A Fine AAA Title", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		_screenWidth, _screenHeight,
		SDL_WINDOW_OPENGL
	);
	if (_window == nullptr)
	{
		fatalError("Window creation failed.");
	}
	// Set up openGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context creation failed.");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Glew init failed.");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.9f, 0.8f, 0.2f, 1.0f);
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << "\n";
			// mouse x is in screen coordinates, from zero to _screenWidth and _screenHeight
			// divide mouse position by screen size to get a zero to one number
			// since in GL we are drawing from -1 to +1
			// multiply the 0 to one value by 2 to get a zero to two range
			// and then subtract one to get a -1 to +1 range
			// finally subtract .5 to put the sprite center at the mouse pointer instead
			// of the corner at the mouse pointer
			_mouseX = (float(evnt.motion.x) / _screenWidth * 2 - 1)+.5;
			_mouseY = (float(evnt.motion.y) / _screenHeight * 2 - 1) * -1 +.5;

			break;
		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		//make sure you make this before you draw your sprite
		_time += 0.1; 
		drawGame();
	}
}

// Draws the game using OpenGL
void MainGame::drawGame()
{
	//_sprite.init(px, py, 1, 1);
	// Sets the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//to make the sprite move with the mouse I am reiniting it every time
	_colorProgram.use();

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	// bringing the mouse position into the shader
	// Get the address of the mouse coordinates variables within the shader. 
	GLuint mouseCoordLocation = _colorProgram.getUniformLocation("mouseCoordinates");
	// get the uniform time before you draw the sprite
	glUniform1f(timeLocation, _time);
	// Send the value into the shader
	glUniform2f(mouseCoordLocation, _mouseX, _mouseY);
	_sprite.draw();
	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

float inc = 0.01f;
float greeeen = 0.01;
void MainGame::sillyDraw()
{
	glClear(GL_GEOMETRY_BIT);
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, inc);
	glVertex2f(-inc, inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, inc);
	glVertex2f(inc, inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -inc);
	glVertex2f(inc, -inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -inc);
	glVertex2f(-inc, -inc);

	glColor3f(0.6, greeeen, 0);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(inc, 0.0f);
	glVertex2f(-inc, inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(inc, 0.0f);
	glVertex2f(inc, inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(-inc, 0.0f);
	glVertex2f(inc, -inc);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(-inc, 0.0f);
	glVertex2f(-inc, -inc);

	glVertex2f(0.2, 0.2);
	glVertex2f(0.2, 0.4);
	glVertex2f(0.4, 0.6);


	inc += 0.01;
	greeeen += 0.01;
	if (inc >= 1.0) {
		inc = 0.01;
		greeeen = 0.01;
	}
	glEnd();
}