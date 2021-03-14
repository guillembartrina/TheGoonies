#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "IScene.h"

class Game
{
	public:

	Game();

	static Game &instance()
	{
		static Game G;
		return G;
	}
	
	void init(int window_width, int window_height, IScene* scene);
	bool update(int deltaTime);
	void render();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	int getWindowWidth() const;
	int getWindowHeight() const;

	void changeScene(IScene* scene);

	private:

	int window_width, window_height;

	bool bPlay;
	bool keys[256], specialKeys[256];

	IScene* scene;

};


#endif // _GAME_INCLUDE


