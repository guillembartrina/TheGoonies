#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE

#include <vector>
#include "glm/glm.hpp"
#include "Texture.h"
#include "Program.h"
#include "AnimKeyframes.h"

class Sprite
{

	public:

	Sprite(const glm::vec2& position, const glm::vec2& size, Texture* spritesheet, const Program& program);
	~Sprite();

	void update(int deltaTime);
	void render(const Program& program) const;

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;
	
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() const;

	private:

	GLuint VAO;
	GLuint VBO;
	GLint posLocation, texCoordLocation;
	Texture* spritesheet;

	glm::vec2 position;

	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;

};


#endif // _SPRITE_INCLUDE

