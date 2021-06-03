#include"Shader.h"
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include"Renderer.h"
Shader::Shader(const std::string& filepath)
	:m_Filepath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);

	m_RendererID = CreateShader(source.VertexSrc, source.FragmentSrc);
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(0));

}

void Shader::Bind() const
{
	GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCALL(glUseProgram(0));
}



void Shader::SetUnifrom1i(const std::string & name, int value)
{
	GLCALL(glUniform1i(GetUnifromLocation(name), value));
}

void Shader::SetUnifrom1f(const std::string & name, int value)
{
	GLCALL(glUniform1f(GetUnifromLocation(name), value));
}

void Shader::SetUnifrom3f(const std::string& name, float f0, float f1, float f2)
{
	GLCALL(glUniform3f(GetUnifromLocation(name), f0, f1, f2));
}

void Shader::SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(GetUnifromLocation(name), v0, v1, v2, v3));
}

void Shader::SetUnifromMat4f(const std::string& name,const glm::mat4 matrix)
{
	GLCALL(glUniformMatrix4fv(GetUnifromLocation(name),1,GL_FALSE,&matrix[0][0]))

}

int Shader::GetUnifromLocation(const std::string& name)
{

	 if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	 {
		 return m_UniformLocationCache[name];
	}
	GLCALL(int location=glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
		m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
			ss[(int)type] << line << '\n';
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char*message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &len, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader"
			<< std::endl << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	
	glDetachShader(program, vs);
	glDetachShader(program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}