#pragma once

#include "graphic_core.hpp"
#include "Texture.hpp"
#include "ShadingProgram.hpp"

#define RECT_VERT_PATH "assets/shaders/rectVert.glsl"
#define RECT_FRAG_PATH "assets/shaders/rectFrag.glsl"

class	Rectangle
{
	static GLuint _vertexArrayID;
	static GLuint _uvArrayID;
	static GLuint _texLocationID;
	static GLuint _dimensionLocationID;
	static GLuint _centerLocationID;
	static ShadingProgram* _program;

	GLuint _textureID;

	float _width;
	float _height;
	glm::vec2 _center;

	void	loadArrayBuffers();
	
public:
	Rectangle(float width, float height, glm::dvec2 center, Texture texture);
	void	Render();
};
