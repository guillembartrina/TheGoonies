#ifndef _SCENE_GAME_INCLUDE
#define _SCENE_GAME_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "Texture.h"
#include "Level.h"
#include "Text.h"


class Scene_Game : public IScene
{

	public:

	Scene_Game();
	~Scene_Game() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	Program program;
	glm::mat4 projection;

	void initShaders();

	Player* player;
	Level* level;

	glm::ivec2 pos;

	Text text;

};


#endif // _SCENE_INCLUDE

