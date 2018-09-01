#pragma once

#include <emscripten.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class	ShadingProgram
{
private:

	GLuint _program;
	std::vector<GLuint> _uniformIDs;
	ShadingProgram(void);

	std::string	GetShaderCode(std::string filepath);
	void	CheckCompilation(GLuint, std::string filepath);
	void	CheckLinking(void);
	
public:
	ShadingProgram(std::string vertexPath, std::string fragPath);
	void	Use(void);
	GLuint	ID(void);
};
