#pragma once

#include <vector>
#include <memory>
#include "graphic_core.hpp"
#include "ShadingProgram.hpp"

#define BACKGROUND_VERT_PATH "bundle/shaders/background.vert"

class Background
{
	static GLuint _vertexArrayID;
	static GLuint _VAO;
	static bool _init;

	std::shared_ptr<ShadingProgram> _program;

	static void	loadArrayBuffers();
	static void	bindArrayBuffers();

public:
	Background(const std::string&);

	void Render(glm::vec2 campos, float scale, float aspect);
};
