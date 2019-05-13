#include "Objects.hpp"

glutil::LightSet::ConstLight::ConstLight(const LightSet *parent, size_t index) : collection(parent),
                                                                                 id(index)
{
}

glm::vec3 glutil::LightSet::ConstLight::GetPosition() const
{
    return glm::vec3(this->collection->data[this->id].position_type.x,
                     this->collection->data[this->id].position_type.y,
                     this->collection->data[this->id].position_type.z);
}

glutil::LightType glutil::LightSet::ConstLight::GetType() const
{
    return static_cast<LightType>(this->collection->data[this->id].position_type.w);
}

glm::vec3 glutil::LightSet::ConstLight::GetColor() const
{
    return glm::vec3(this->collection->data[this->id].color_ambientFactor.r,
                     this->collection->data[this->id].color_ambientFactor.g,
                     this->collection->data[this->id].color_ambientFactor.b);
}

float glutil::LightSet::ConstLight::GetAmbientFactor() const
{
    return this->collection->data[this->id].color_ambientFactor.a;
}

bool glutil::LightSet::ConstLight::IsActive() const
{
    return this->collection->data[this->id].spotExponent_size_enabled.w;
}