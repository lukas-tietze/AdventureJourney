#include "Objects.hpp"

glutil::LightSet::Light::Light(LightSet *c, size_t i) : ConstLight(c, i),
                                                        modifiableCollection(c)
{
}

glutil::LightSet::Light &glutil::LightSet::Light::SetPosition(const glm::vec3 &pos)
{
    this->modifiableCollection->data[this->id].position_type.x = pos.x;
    this->modifiableCollection->data[this->id].position_type.y = pos.y;
    this->modifiableCollection->data[this->id].position_type.z = pos.z;
    this->modifiableCollection->SetDirty();
}

glutil::LightSet::Light &glutil::LightSet::Light::SetType(LightType type)
{
    this->modifiableCollection->data[this->id].position_type.w = static_cast<uint32_t>(type);
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetColor(const glm::vec3 &clr)
{
    this->modifiableCollection->data[this->id].color_ambientFactor.r = clr.r;
    this->modifiableCollection->data[this->id].color_ambientFactor.g = clr.g;
    this->modifiableCollection->data[this->id].color_ambientFactor.b = clr.b;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetAmbientFactor(float f)
{
    this->modifiableCollection->data[this->id].color_ambientFactor.a = f;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetActive(bool active)
{
    this->modifiableCollection->data[this->id].spotExponent_size_enabled.w = active;
    this->modifiableCollection->SetDirty();

    return *this;
}
