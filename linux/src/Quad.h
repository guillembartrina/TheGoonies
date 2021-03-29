#ifndef _QUAD_INCLUDE
#define _QUAD_INCLUDE


#include "glm/glm.hpp"
#include "Texture.h"
#include "Program.h"


class Quad
{

	public:

	static Quad *createQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color,  Program &program);

	Quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Program &program);
	~Quad();

	void render(const Program &program) const;

	private:
	
	GLuint vao;
	GLuint vbo;
	GLint posLocation;

	glm::vec4 color;

};


#endif // _QUAD_INCLUDE

