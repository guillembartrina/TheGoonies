#ifndef _SCENE_MENU_INCLUDE
#define _SCENE_MENU_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "Texture.h"
#include "Level.h"
#include "Text.h"


class Scene_Menu : public IScene
{

	public:

	Scene_Menu();
	~Scene_Menu() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	glm::mat4 projection;

	Text text;

};


#endif // _SCENE_INCLUDE

