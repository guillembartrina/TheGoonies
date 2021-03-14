
#ifndef _PROGRAM_INCLUDE
#define _PROGRAM_INCLUDE

#include <utility>
#include <vector>

#include <GL/glew.h>
#include "glm/glm.hpp"

#include "Shader.h"

class Program
{
	public:

	Program();
	~Program();

	void attachShader(const Shader& shader);

	void defineAttributesLocation(const std::vector<std::pair<std::string, GLuint>>& data);

	bool link();

	GLuint getAttributeLocation(const std::string& name) const;
	GLuint getUniformLocation(const std::string& name) const;

	GLuint getId() const;

	void use() const;

	void setUniformValue(GLuint location, int value) const;
	void setUniformValue(GLuint location, float value) const;
	void setUniformValue(GLuint location, const glm::vec2& value) const;
	void setUniformValue(GLuint location, const glm::vec3& value) const;
	void setUniformValue(GLuint location, const glm::vec4& value) const;
	void setUniformValue(GLuint location, const glm::mat3& value) const;
	void setUniformValue(GLuint location, const glm::mat4& value) const;
	void setUniformValue(GLuint location, const std::vector<glm::vec3>& value) const;

	bool isLinked() const;
	bool isAttached(ShaderType type) const;

	static const Program* getActiveProgram();

	private:

	GLuint id;
	GLuint shaderIds[ShaderType_NUM];

	bool linked;

	static const Program* activeProgram;
};

#endif // _PROGRAM_INCLUDE
	
