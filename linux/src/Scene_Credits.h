#ifndef _SCENE_CREDITS_INCLUDE
#define _SCENE_CREDITS_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "Texture.h"
#include "Level.h"
#include "Text.h"


class Scene_Credits : public IScene
{

	public:

	Scene_Credits();
	~Scene_Credits() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	Text text;

};


#endif // _SCENE_INCLUDE

