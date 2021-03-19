#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"
#include "Scene_Menu.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


#define TIME_PER_FRAME 1000.f / 60.f
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

static void keyboardDownCallback(unsigned char key, int x, int y)
{
	Game::instance().keyPressed(key);
}

static void keyboardUpCallback(unsigned char key, int x, int y)
{
	Game::instance().keyReleased(key);
}

static void specialDownCallback(int key, int x, int y)
{
	Game::instance().specialKeyPressed(key);
}

static void specialUpCallback(int key, int x, int y)
{
	Game::instance().specialKeyReleased(key);
}

static void motionCallback(int x, int y)
{
	Game::instance().mouseMove(x, y);
}

static void mouseCallback(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) Game::instance().mousePress(button);
	else if(state == GLUT_UP) Game::instance().mouseRelease(button);
}

static void drawCallback()
{
	Game::instance().render();
	glutSwapBuffers();
}

static int prevTime;

static void idleCallback()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - prevTime;
	
	if(deltaTime > TIME_PER_FRAME)
	{
		if(!Game::instance().update(deltaTime)) exit(0);
		prevTime = currentTime;
		glutPostRedisplay();
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow(argv[0]);
	glutDisplayFunc(drawCallback);
	glutIdleFunc(idleCallback);
	glutKeyboardFunc(keyboardDownCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(specialDownCallback);
	glutSpecialUpFunc(specialUpCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);

	glewExperimental = GL_TRUE;
	glewInit();
	
	Game::instance().init(WINDOW_WIDTH, WINDOW_HEIGHT, new Scene_Menu());
	prevTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	return 0;
}



