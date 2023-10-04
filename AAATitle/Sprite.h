#pragma once
#include <GL/glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);


	void draw();

	float _x;
	float _y;
	float _width;
	float _height;
	// similar to an unsigned int guarenteed to be 32bits
	GLuint _vboID;
};

