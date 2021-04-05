#ifndef _SENSOR_INCLUDE
#define _SENSOR_INCLUDE

#include "Entity.h"

enum SensorType {VINE_TOP, VINE_BOTTOM, ROCK, SKELETON, PORTAL, HITBOX,END};

class Sensor : public Entity
{

	public:

	Sensor(SensorType type, const glm::vec2 &pos, const glm::vec2 &size, int code = 0);

    SensorType getType() const;
	int getCode() const;

	protected:

    SensorType type;
	int code;

};

#endif // _SENSOR_INCLUDE