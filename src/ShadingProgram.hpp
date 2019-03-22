#pragma once

#include <emscripten.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

class	ShadingProgram
{
	GLuint _program;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	std::map<std::string, GLuint> _uniforms;

	ShadingProgram(void);
	void _getUniforms();
	std::string _getShaderCode(std::string filepath);
	void _checkCompilation(GLuint, std::string filepath);
	void _checkLinking();

public:
	ShadingProgram(std::string vertexPath, std::string fragPath);
	~ShadingProgram();
	void Use();
	GLuint Uniform(const std::string&);
};
