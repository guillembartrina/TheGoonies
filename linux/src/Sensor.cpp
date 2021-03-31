
#include "Sensor.h"

Sensor::Sensor(SensorType type, const glm::vec2 &pos, const glm::vec2 &size, int code) : Entity(EntityType::SENSOR, pos, size)
{
    this->type = type;
    this->code = code;
}

SensorType Sensor::getType() const
{
    return type;
}

int Sensor::getCode() const
{
    return code;
}