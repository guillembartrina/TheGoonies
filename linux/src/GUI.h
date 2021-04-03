#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Texture.h"
#include "Quad.h"
#include "Text.h"
#include "Entity.h"
#include "Player.h"

class GUI
{

	public:

	GUI(const glm::mat4& projection, const glm::vec4& rect, Player *player, Program &programTexture);
	~GUI();

	void update(int deltatime);
	void render(Program &programTexture);

	private:

	Program program;
	glm::mat4 projection;

	Text text;
    Quad* background, * maxVitBar, * vitBar, * expMaxBar, * expBar;
	Player *player;
	Texture *texture;
	Sprite * powerupFrames;
};

#endif // _GUI_INCLUDE