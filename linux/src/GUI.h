#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE

#include <string>
#include <vector>

#include "Program.h"
#include "Texture.h"
#include "Quad.h"
#include "Text.h"
#include "Entity.h"
#include "Player.h"

class GUI
{

	public:

	GUI(const glm::mat4& projection, const glm::vec4& rect);
	~GUI();

	void update(int deltatime);
	void render();

	private:

	Program program;
	glm::mat4 projection;

	Text text;
    Quad* background;

};

#endif // _GUI_INCLUDE