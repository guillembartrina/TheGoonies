
#include "Shader.h"

#include <iostream>
#include <fstream>


Shader::Shader(ShaderType type)
{
    GLenum t;
    switch(type)
    {
        case ShaderType_Vertex:
            t = GL_VERTEX_SHADER;
            break;
        case ShaderType_Geomerty:
            t = GL_GEOMETRY_SHADER;
            break;
        case ShaderType_Fragment:
            t = GL_FRAGMENT_SHADER;
            break;
    }
    this->type = type;
    id = glCreateShader(t);
    loaded = false;
    compiled = false;
}

Shader::~Shader()
{
	glDeleteShader(id);
}

void Shader::load_fromString(const std::string& source)
{
    const GLchar* src = source.c_str();
    glShaderSource(id, 1, &src, 0);
    loaded = true;
    compiled = false;
}

bool Shader::load_fromFile(const std::string& path)
{
    std::string source;
    if(not readFile(path, source)) return false;
    const GLchar* src = source.c_str();
    glShaderSource(id, 1, &src, 0);
    loaded = true;
    compiled = false;
    return true;
}

bool Shader::compile()
{
    if(loaded)
    {
        glCompileShader(id);
        GLint compiledFlag;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compiledFlag);
        if(compiledFlag == GL_FALSE)
        {
            GLint lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* log = (char*)malloc(lenght);
            glGetShaderInfoLog(id, lenght, &lenght, log);
            std::cerr << "Shader: compiling error" << std::endl << log << std::endl;
            free((void*)log);
            return false;
        }
        compiled = true;
        return true;
    }
    else
    {
        std::cerr << "Shader: error compiling, shader not loaded" << std::endl;
    }
    return false;
}

ShaderType Shader::getType() const
{
    return type;
}

GLuint Shader::getId() const
{
    return id;
}

bool Shader::isLoaded() const
{
    return loaded;
}

bool Shader::isCompiled() const
{
    return compiled;
}

bool Shader::readFile(const std::string& path, std::string& source)
{
	std::ifstream fin;
	fin.open(path.c_str());
	if(!fin.is_open()) return false;
	source.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	return true;
}