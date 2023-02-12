#include"shaderprogram.hpp"
#include"glad/glad.h"
#include<fstream>
#include<iostream>

ShaderProgram::ShaderProgram() 
{
	m_ProgramID = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramID);
}
void ShaderProgram::link()
{
	glLinkProgram(m_ProgramID);
	int isLinked;
	char log[512];
	glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		glGetShaderInfoLog(m_ProgramID, 512, 0, log);
		std::cout << "Program Linking Error:" << std::endl << log << std::endl;
	}

}
void ShaderProgram::use()
{
	glUseProgram(m_ProgramID);
}
void ShaderProgram::addUniform(const std::string& varName)
{
	m_UniformVars[varName] = glGetUniformLocation(m_ProgramID, varName.c_str());
}

void ShaderProgram::setFloat(const std::string& varName, float value)
{
	glUniform1f(m_UniformVars[varName], value);
}

void ShaderProgram::setVec3(const std::string& varName, const glm::vec3& value)
{
	glUniform3f(m_UniformVars[varName], value.x, value.y, value.z);
}

void ShaderProgram::setVec4(const std::string& varName, const glm::vec4& value)
{
	glUniform4f(m_UniformVars[varName], value.r, value.g, value.b, value.a);
}

void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType)
{
	unsigned int shaderID = glCreateShader(shaderType);

	std::string sourceCode = getShaderFromFile(fileName);

	const char* chSourceCode = &sourceCode[0];

	glShaderSource(shaderID, 1, &chSourceCode, 0);

	glCompileShader(shaderID);

	int isCompiled;
	char log[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) 
	{
		glGetShaderInfoLog(shaderID, 512, 0, log);
		std::cout << "Shader Type:" << shaderType << std::endl << log << std::endl;
	}

	glAttachShader(m_ProgramID, shaderID);

	glDeleteShader(shaderID);
}
std::string ShaderProgram::getShaderFromFile(const char* fileName)
{
	std::ifstream file(fileName);

	std::string data;

	if (file.is_open()) 
	{
		char readChar;

		while ((readChar = file.get()) != EOF) 
		{
			data += readChar;
		}

		file.close();
	}

	return data;
}