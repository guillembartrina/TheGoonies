#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"


Sprite::Sprite(const glm::vec2& position, const glm::vec2& size, Texture* spritesheet, const Program& program)
{
	float vertices[24] = {0.f, 0.f, 0.f, 0.f, 
							size.x, 0.f, 1.f, 0.f, 
							size.x, size.y, 1.f, 1.f, 
							0.f, 0.f, 0.f, 0.f, 
							size.x, size.y, 1.f, 1.f, 
							0.f, size.y, 0.f, 1.f};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	GLint posLocation = program.getAttributeLocation("position");
	glVertexAttribPointer(program.getAttributeLocation("position"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	glEnableVertexAttribArray(posLocation);
	GLint texCoordLocation = program.getAttributeLocation("texCoord");
	glVertexAttribPointer(program.getAttributeLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)(2*sizeof(float)));
	glEnableVertexAttribArray(texCoordLocation);
	this->spritesheet = spritesheet;
	currentAnimation = -1;
	this->position = position;
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &VBO);
	delete spritesheet;
}

void Sprite::update(int deltaTime)
{
	if(currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render(const Program& program) const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	program.setUniformValue(program.getUniformLocation("modelview"), modelview);
	//program.setUniformValue(program.getUniformLocation("texCoordDispl"), glm::vec2(texCoordDispl.x, texCoordDispl.y));
	spritesheet->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if(animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

void Sprite::setPosition(const glm::vec2& pos)
{
	position = pos;
}

glm::vec2 Sprite::getPosition() const
{
	return position;
}



