#ifndef _SCENE2_INCLUDE
#define _SCENE2_INCLUDE


#include "glm/glm.hpp"

#include "IScene.h"
#include "Program.h"
#include "TileMap.h"


class Scene2 : public IScene
{

	public:

	Scene2();
	~Scene2() override;

	void init() override;
	void update(int deltaTime) override;
	void render() override;

	private:

	Program program;
	glm::mat4 projection;

	TileMap *map;

	void initShaders();

	GLuint rectVAO;
	GLuint rectiVBO, rectvVBO, recttVBO;

	GLint posLocation, texCoordLocation;

	Texture texture;

};


#endif // _SCENE_INCLUDE

