#include "GLSLProgram.h"
#include "errors.h"
#include <fstream>
#include <vector>

// QUESTION FOR NATHAN
// in the tutorial ben uses this initialization list and says it is faster
// is this still necessary or is it a practice for old versions
// and with modern compilers this is something the compiler will just take care of now?
GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)

{
}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	// for each of these numAttributes we need to enable the vertex attrib array 
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
	// 0 is the same as saying no not use program
	glUseProgram(0);
}

void readFile(const std::string& path, std::string & result) {
	std::ifstream file(path);
	if (file.fail()) {
		fatalError("Failed to open " + path);
	}

	std::string contents(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);
	result += contents;
	file.close();
}

void compileShader(const std::string & filepath, GLuint & shaderID)
{
	std::string fileContents = "";
	readFile(filepath, fileContents);
	std::cout << fileContents;

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);
	GLint success = 0;
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID);
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Failed to compile shader "+filepath);
	}
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	// Vertex and fragment shaders are successfui
	//Get the program object
	_programID = glCreateProgram();

	// Create the vertex shader object, and store its ID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatalError("Failed to create vertex shader");

	// Create the fragment shader object, and store its ID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
		fatalError("Failed to create fragment shader");

	// this is where we compile each shader. 
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName)
{
	// the name will be a pointe to char, so c_str()
	// ++ after num attr will add one AFTER the line of code runs
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform shader variable location retrieval for " + uniformName + " failed");
	}
	return location;
}

void GLSLProgram::linkShaders() {
	//attach our shaders to the program 
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// the maxLength includes the NULL character 
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
		std::printf("%s\n", &(infoLog[0]));

		// We dont need the program anymore 
		glDeleteProgram(_programID);
		//Dont leak shaders either
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		// print the error log and quit
		fatalError("Shader linking failed, oh boy oh boy I really hope this doesn't happen.");
	}
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}