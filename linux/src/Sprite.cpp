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
	this->position = position;
	currentFrame = -1;
	currentAnimation = -1;
}

Sprite::~Sprite()
{
	for(Animation* a : animations)
	{
		delete a;
	}
	for(Frame* f : frames)
	{
		delete f;
	}
	delete spritesheet;
	glDeleteBuffers(1, &VBO);
}

void Sprite::update(int deltaTime)
{
	if(currentAnimation >= 0)
	{
		currentTime += deltaTime;
		while(currentTime > animations[currentAnimation]->keyframes[currentKeyFrame]->duration)
		{
			currentTime -= animations[currentAnimation]->keyframes[currentKeyFrame]->duration;
			currentKeyFrame = (currentKeyFrame + 1) % animations[currentAnimation]->keyframes.size();
		}
		currentFrame = animations[currentAnimation]->keyframes[currentKeyFrame]->id;
	}
}

void Sprite::render(const Program& program, const glm::mat4 &modelview) const
{
	glm::mat4 mv = glm::translate(glm::mat4(modelview), glm::vec3(position.x, position.y, 0.f));
	program.setUniformValue(program.getUniformLocation("modelview"), mv);

	if(currentFrame == -1)
	{
		program.setUniformValue(program.getUniformLocation("customTexCoord"), 0);
	}
	else
	{
		program.setUniformValue(program.getUniformLocation("customTexCoord"), 1);
		program.setUniformValue(program.getUniformLocation("frame"),
			glm::vec4(frames[currentFrame]->u, frames[currentFrame]->v, frames[currentFrame]->w, frames[currentFrame]->h));
	}
	//program.setUniformValue(program.getUniformLocation("texCoordDispl"), glm::vec2(texCoordDispl.x, texCoordDispl.y));
	spritesheet->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::addFrame(Frame* frame)
{
	frames.push_back(frame);
}

void Sprite::addAnimation(Animation* animation)
{
	animations.push_back(animation);
}

void Sprite::setFrame(int id)
{
	if(id >= -1 && id < int(frames.size())) currentFrame = id;
}

void Sprite::setAnimation(int id)
{
	if(id >= -1 && id < int(animations.size()))
	{
		currentAnimation = id;
		currentKeyFrame = 0;
		currentFrame = animations[id]->keyframes[0]->id;
		currentTime = 0.f;
	}
}

int Sprite::getAnimation() const
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



