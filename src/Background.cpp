#include "Background.hpp"

GLuint Background::_vertexArrayID;
GLuint Background::_VAO;
bool Background::_init = false;

void	Background::loadArrayBuffers()
{
	const float vertex_array[] = {
		+1, -1, -1, -1, +1, +1,
		-1, +1, -1, -1, +1, +1
	};
	glGenBuffers(1, &_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertex_array),
		vertex_array,
		GL_STATIC_DRAW
	);
}

void	Background::bindArrayBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

Background::Background(const std::string& frag_path)
{
	_program = std::make_shared<ShadingProgram>(
		BACKGROUND_VERT_PATH, frag_path);
	if (!_init)
	{
		loadArrayBuffers();
		bindArrayBuffers();
	}
}

void Background::Render(glm::vec2 campos, float scale, float aspect)
{
	_program->Use();
	
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(_VAO);

	glUniform2f(_program->Uniform("campos"), campos.x, campos.y);
	glUniform1f(_program->Uniform("scale"), scale);
	glUniform1f(_program->Uniform("aspect"), aspect);
	
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
}
