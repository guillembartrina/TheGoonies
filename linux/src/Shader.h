
#ifndef _SHADER_INCLUDE
#define _SHADER_INCLUDE

#include <string>

#include <GL/glew.h>

enum ShaderType
{
	ShaderType_Vertex = 0,
	ShaderType_Geomerty,
	ShaderType_Fragment,
	ShaderType_NUM
};

class Shader
{
	public:

	Shader(ShaderType type);
	~Shader();

	void load_fromString(const std::string& source);
	bool load_fromFile(const std::string& path);

	bool compile();

	ShaderType getType() const;
	GLuint getId() const;

	bool isLoaded() const;
	bool isCompiled() const;

	private:

	ShaderType type;
	GLuint id;

	bool loaded;
	bool compiled;

	bool readFile(const std::string& path, std::string& source);
};

#endif // _SHADER_INCLUDE