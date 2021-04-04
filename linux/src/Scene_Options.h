#ifndef _SCENE_OPTIONS_INCLUDE
#define _SCENE_OPTIONS_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "Texture.h"
#include "Level.h"
#include "Text.h"


class Scene_Options : public IScene
{

	public:

	Scene_Options();
	~Scene_Options() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	Text textBold, text;

};


#endif // _SCENE_INCLUDE

