#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();

private:
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();

	void sillyDraw();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	float _mouseX;
	float _mouseY;

	float _time;

	Sprite _sprite;
	// the basic color and shader program
	GLSLProgram _colorProgram;
};