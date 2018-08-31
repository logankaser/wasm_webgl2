#include "Rectangle.hpp"

GLuint Rectangle::_vertexArrayID;
GLuint Rectangle::_uvArrayID;
GLuint Rectangle::_texLocationID;
GLuint Rectangle::_dimensionLocationID;
GLuint Rectangle::_centerLocationID;
ShadingProgram* Rectangle::_program = nullptr;

Rectangle::Rectangle(float width, float height, glm::dvec2 center, Texture texture) :
_width(width),
_height(height),
_center(center)
{
	if (!_program)
	{
		_program = new ShadingProgram(RECT_VERT_PATH, RECT_FRAG_PATH);
		_texLocationID = glGetUniformLocation(_program->ID(), "tex");
		_dimensionLocationID = glGetUniformLocation(_program->ID(), "dimension");
		_centerLocationID = glGetUniformLocation(_program->ID(), "center");
		loadArrayBuffers();
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     texture.width,
		     texture.height,
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     texture.data);
}

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

void	Rectangle::Render()
{
	_program->Use();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _textureID);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_texLocationID, 0);

	glUniform2f(_dimensionLocationID, _width, _height);
	glUniform2f(_centerLocationID, _center.x, _center.y);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
