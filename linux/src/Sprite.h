#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE

#include <vector>
#include "glm/glm.hpp"
#include "Texture.h"
#include "Program.h"

struct Frame
{
	Frame(float u, float v, float w, float h) : u(u), v(v), w(w), h(h) {}
	
	float u, v, w, h;
};

struct KeyFrame
{
	KeyFrame(int id, float duration) : id(id), duration(duration) {}

	int id;
	float duration;
};


struct Animation
{
	Animation(const std::vector<int>& ids, const std::vector<float>& times)
	{
		for(int i = 0; i < int(ids.size()); i++)
		{
			keyframes.push_back(new KeyFrame(ids[i], times[i]));
		}
	}

	~Animation()
	{
		for(KeyFrame* kf : keyframes)
		{
			delete kf;
		}
	}

	std::vector<KeyFrame *> keyframes;
};

class Sprite
{

	public:

	Sprite(const glm::vec2& position, const glm::vec2& size, Texture* spritesheet, const Program& program);
	~Sprite();

	void update(int deltaTime);
	void render(const Program& program) const;

	void addFrame(Frame* frame);
	void addAnimation(Animation* animation);
	void setFrame(int id);
	void setAnimation(int id);
	int getAnimation() const;
	
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() const;

	private:

	GLuint VAO;
	GLuint VBO;
	Texture* spritesheet;

	glm::vec2 position;

	int currentAnimation, currentFrame, currentKeyFrame;
	float currentTime;
	std::vector<Frame *> frames;
	std::vector<Animation *> animations;

};


#endif // _SPRITE_INCLUDE

