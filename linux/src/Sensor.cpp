
#include "Sensor.h"

Sensor::Sensor(const glm::vec2 &pos, const glm::vec2 &size, const Program& program) : Entity(EntityType::SENSOR, pos, size, nullptr, program) {}

SensorType Sensor::getType() const
{
    return type;
}