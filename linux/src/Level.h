#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>
#include <vector>
#include <list>

#include "Program.h"
#include "Texture.h"
#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"

static glm::ivec2 roomSize = glm::ivec2(32, 20);
static glm::vec2 tileSize = glm::vec2(16.f, 16.f);
static glm::vec2 floorOffset = glm::vec2(0.f, -2.f);

static int stoppingTime = 5000;

enum CollisionType { FULL, TOP, BOTTOM, LEFT, RIGHT, ANY };


class Level
{

	public:

	Level(const std::string& path, const Program& program);
	~Level();

	void spawnPlayer(Player* player, int code);

	void render(const glm::vec4& rect, const Program& program) const;
	void update(int deltatime);

	glm::ivec2 getMapSize() const;
	Player* getPlayer();
	std::list<Entity *>& getEntities();
	bool inScreen(const glm::vec2& pos) const;

	bool collisionMoveLeft(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const;
	bool collisionMoveRight(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const;
	bool collisionMoveUp(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const;
	bool collisionMoveDown(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const;

	bool getFirstOf(const glm::vec2& pos, const glm::vec2& size, int direction, glm::vec2& first) const;
	bool getFirstOf_Tiles(const glm::ivec2& ini, int direction, CollisionType type, glm::ivec2& first) const;

	void addEntity(Entity* entity);

	void stopTime();
	bool isTimeStopped() const;

	private:

	std::string name;
	glm::ivec2 mapSize;
	int* map;
	Tilesheet* tilesheet, *movingsheet;
	glm::vec2 spawnPos;
	CollisionType collisionMap[96];
	
	Player* player;
	std::list<Entity *> entities;
	Tilemap* tileMap;

	glm::ivec2 cam;
	std::vector<glm::vec2> portals;

	int stopTimer;

	bool load(const std::string& path, const Program& program);
	glm::vec2 roomRelativeToWorldCoords(glm::ivec2* roomPositions, int room, glm::ivec2 coords) const;

};

#endif // _LEVEL_INCLUDE