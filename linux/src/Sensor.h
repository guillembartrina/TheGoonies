#ifndef _SENSOR_INCLUDE
#define _SENSOR_INCLUDE

#include "Entity.h"

enum SensorType {VINE_TOP, VINE_BOTTOM, ROCK};

class Sensor : public Entity
{

	public:

	Sensor(SensorType type, const glm::vec2 &pos, const glm::vec2 &size);

    SensorType getType() const;

	protected:

    SensorType type;

};

#endif // _SENSOR_INCLUDE