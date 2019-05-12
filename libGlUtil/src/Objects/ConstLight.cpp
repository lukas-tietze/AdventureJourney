#include "Objects.hpp"

glutil::LightSet::ConstLight::ConstLight(const LightSet *parent, size_t index) : collection(parent),
                                                                                                                                       id(index)
{
}

const glm::vec3 &glutil::LightSet::ConstLight::GetPosition() const
{
    return this->collection->data[this->id].position;
}

glutil::LightType glutil::LightSet::ConstLight::GetType() const
{
    return static_cast<LightType>(this->collection->data[this->id].type);
}

const glm::vec3 &glutil::LightSet::ConstLight::GetColor() const
{
    return this->collection->data[this->id].color;
}

float glutil::LightSet::ConstLight::GetAmbientFactor() const
{
    return this->collection->data[this->id].ambientFactor;
}

bool glutil::LightSet::ConstLight::IsActive() const
{
    return this->collection->data[this->id].active;
}