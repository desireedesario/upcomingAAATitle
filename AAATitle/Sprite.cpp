#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
#include <cmath>

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

// using #define to make a macro
// macro is a text replacement that happens before compilation
// the pre processor will replace the text EIGHTBITCOLOR(0.6) with this text
// unsigned char(0.6)
// and most likely the compiler will replace unsigned char(0.6) with the converted
// value during optimization so this seems like it should end up being just as fast
// as what the tutorial does where numbers between 0 and 255 are hardcoded
// but is more future proof in case of using floating point color later
#define EIGHTBITCOLOR(c) unsigned char(c * 255)

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	//generate the buffer
	// only initialize it if it has not been generated yet
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	
	// a list of six vertex objects for two triangles to make one quad
	Vertex vertexData[6];

	//first triangle top left
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	//first triangle top right
	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	//first triangle bottom
	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		//change colors when the mouse moved (before mouse movement was sent to the shader. This doesnt update anymore. 
		vertexData[i].color.r = EIGHTBITCOLOR(abs(x));
		// makes each vertex have a different color for green based on its number
		// this made different colors on each triangle that made the square sprite
		// vertexData[i].color.g = EIGHTBITCOLOR(float(i)/5);
		vertexData[i].color.g = EIGHTBITCOLOR(0.8);
		vertexData[i].color.b = EIGHTBITCOLOR(0.9);
		vertexData[i].color.a = EIGHTBITCOLOR(1.0);
	}
	//pushes into the vertex buffer object
	// bind the buffer: we want this buffer to be active
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// upload the bufer data
	// sizeof(vertexData) is how many bytes of data 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// unbind the buffer
	// NATHAN: why would we want to unbind the buffer?
	// nvm, no need to hold on to the vram buffer data anymore
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	// bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// Tell opengl that we want to use the first
	// attribute array. We only need one array right now
	// since we are only using position
	glEnableVertexAttribArray(0);

	// Point opengl to the data in the VBO.This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// passing TRUE for normalize, not sure why we don't just use floats in the first place Ben
	// This is the color attribute pointer 
	// (void*)offsetof(Vertex, color) uses the Vertex struct and find the osset of color which is going to return 8
	// since its 8bytes after the beginning of the position
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Draw six triangles using the data in the VBO
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disable the vertex attrib array. Not optional.
	glDisableVertexAttribArray(0);

	// unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}