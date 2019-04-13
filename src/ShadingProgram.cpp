#include "ShadingProgram.hpp"

ShadingProgram::ShadingProgram(void) {}

ShadingProgram::ShadingProgram(std::string vp, std::string fp)
{
	_program = 0;
	_vertexShaderID = 0;
	_fragmentShaderID = 0;

	const char* shader_src;

	_program = glCreateProgram();
	std::string vert = _getShaderCode(vp);
	shader_src = vert.data();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShaderID, 1, &shader_src, nullptr);
	glCompileShader(_vertexShaderID);
	_checkCompilation(_vertexShaderID, vp);
	glAttachShader(_program, _vertexShaderID);

	std::string frag = _getShaderCode(fp);
	shader_src = frag.data();
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderID, 1, &shader_src, nullptr);
	glCompileShader(_fragmentShaderID);
	_checkCompilation(_fragmentShaderID, fp);
	glAttachShader(_program, _fragmentShaderID);
	glLinkProgram(_program);
	_checkLinking();
	_getUniforms();
}

ShadingProgram::~ShadingProgram()
{
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_program);
}

std::string	ShadingProgram::_getShaderCode(std::string filepath)
{
	std::ifstream fileStream(filepath);

	if (fileStream.fail() || !fileStream.good())
	{
		std::cerr << "Cannot read shader file: " << filepath << std::endl;
	}
	std::stringstream buf;
	buf << fileStream.rdbuf();
	return buf.str();
}

void	ShadingProgram::_checkCompilation(GLuint id, std::string path)
{
	GLint success = 0;
	GLint logsize;

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);

		char *log = new char[logsize];

		glGetShaderInfoLog(id, logsize, nullptr, log);
		std::cerr << "Error compiling shader "
			<< "src: \"" << path << '"' << std::endl
			<< log << std::endl << std::endl;
		delete[] log;
	}
}

void	ShadingProgram::_checkLinking()
{
	GLint success = 0;
	GLint logsize;

	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logsize);

		char *log = new char[logsize];

		glGetProgramInfoLog(_program, logsize, nullptr, log);
		std::cerr << "Error linking shader program:" << std::endl << log << std::endl;
		delete[] log;
	}
}

void	ShadingProgram::_getUniforms()
{
	for (auto& p : _uniforms)
		p.second = glGetUniformLocation(_program, p.first.c_str());
}

GLuint	ShadingProgram::Uniform(const std::string& name)
{
	if (_uniforms.count(name) == 0)
		_uniforms[name] = glGetUniformLocation(_program, name.c_str());
	return _uniforms[name];
}

void	ShadingProgram::Use(void)
{
	glUseProgram(_program);
}
