#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "Texture.h"
#include "Level.h"
#include "Text.h"


class Scene : public IScene
{

	public:

	Scene();
	~Scene() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	Program program;
	glm::mat4 projection;

	void initShaders();

	Level* level;

	glm::ivec2 pos;

	Text text;

};


#endif // _SCENE_INCLUDE

