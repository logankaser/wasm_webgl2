#pragma once

#include <vector>
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
	static GLuint _VAO;
	static ShadingProgram* _program;

	static void	loadArrayBuffers();
	static void	bindArrayBuffers();
	
public:

	float width;
	float height;
	glm::vec2 center;
	GLuint textureID;

	// for optimal rendering, place rectangles with the same textureIDs
	// next to each other
	static void	Render(const std::vector<Rectangle>&);
};
