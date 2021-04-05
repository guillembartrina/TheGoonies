#pragma once

#include "Sensor.h"

class Hitbox : public Sensor
{
public:
	Hitbox(const glm::vec2 &pos, const glm::vec2 &size);
	
	void setActive(int activeTime);
	bool isActive();
	void update(int deltatime);

private:
	int activeCounter;
};