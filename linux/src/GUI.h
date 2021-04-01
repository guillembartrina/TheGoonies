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

	GUI(const glm::mat4& projection, const glm::vec4& rect, int vit, int exp);
	~GUI();

	void update(int deltatime, int vit, int exp);
	void render();

	private:

	Program program;
	glm::mat4 projection;

	Text text;
    Quad* background;
	int vit;
	int exp;

};

#endif // _GUI_INCLUDE