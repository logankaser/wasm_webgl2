#include "Rectangle.hpp"

GLuint Rectangle::_vertexArrayID;
GLuint Rectangle::_uvArrayID;
GLuint Rectangle::_texLocationID;
GLuint Rectangle::_dimensionLocationID;
GLuint Rectangle::_centerLocationID;
GLuint Rectangle::_VAO;
ShadingProgram* Rectangle::_program = nullptr;

void	Rectangle::loadArrayBuffers()
{
	const float vertex_array[] = { 0.5, -0.5, -0.5, -0.5,  0.5,  0.5,
				      -0.5,  0.5, -0.5, -0.5,  0.5,  0.5};
	glGenBuffers(1, &_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(vertex_array),
		     vertex_array,
		     GL_STATIC_DRAW);

	const float uv_array[] = {1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1};
	glGenBuffers(1, &_uvArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(uv_array),
		     uv_array,
		     GL_STATIC_DRAW);
}

void	Rectangle::bindArrayBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void	Rectangle::Render(const std::vector<Rectangle>& rectangles)
{
	if (!_program)
	{
		_program = new ShadingProgram(RECT_VERT_PATH, RECT_FRAG_PATH);
		_texLocationID = glGetUniformLocation(_program->ID(), "tex");
		_dimensionLocationID = glGetUniformLocation(_program->ID(), "dimension");
		_centerLocationID = glGetUniformLocation(_program->ID(), "center");
		loadArrayBuffers();
		bindArrayBuffers();
	}
	_program->Use();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(_VAO);

	for (unsigned i = 0; i < rectangles.size(); i++)
	{
		if (!i || rectangles[i].textureID != rectangles[i - 1].textureID)
		{
			glBindTexture(GL_TEXTURE_2D, rectangles[i].textureID);
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(_texLocationID, 0);
		}
		glUniform2f(_dimensionLocationID, rectangles[i].width, rectangles[i].height);
		glUniform2f(_centerLocationID, rectangles[i].center.x, rectangles[i].center.y);

		glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
	}
}
