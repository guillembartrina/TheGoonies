#include <GL/glew.h>
#include <GL/gl.h>
#include "Quad.h"


Quad *Quad::createQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Program &program)
{
	Quad *quad = new Quad(pos, size, color, program);

	return quad;
}

Quad::Quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Program &program)
{
	float vertices[12] = {pos.x, pos.y, pos.x + size.x, pos.y,
						  pos.x + size.x, pos.y + size.y, pos.x,
						  pos.y, pos.x + size.x, pos.y + size.y,
						  pos.x, pos.y + size.y };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.getAttributeLocation("position");
	glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	this->color = color;
}

Quad::~Quad()
{
	glDeleteBuffers(1, &vbo);
}

void Quad::render(const Program &program) const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	program.setUniformValue(program.getUniformLocation("color"), color);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
