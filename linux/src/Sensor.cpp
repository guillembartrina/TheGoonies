
#include "Sensor.h"

Sensor::Sensor(SensorType type, const glm::vec2 &pos, const glm::vec2 &size) : Entity(EntityType::SENSOR, pos, size)
{
    this->type = type;
}

SensorType Sensor::getType() const
{
    return type;
}