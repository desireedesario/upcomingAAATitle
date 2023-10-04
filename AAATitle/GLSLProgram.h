#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath);

	void linkShaders();

	// add the attr to the next available slot 
	// attributeName is the nextvattr name
	void addAttribute(const std::string &attributeName);
	
	//get the uniform location
	GLint getUniformLocation(const std::string& uniformName);
	
	// bind the program
	void use();
	//unbind the program
	void unuse();

private:
	// counting the num of attrs we have 
	int _numAttributes;
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

