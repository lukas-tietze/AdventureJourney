#include "Objects.hpp"

glutil::LightSet::Light::Light(LightSet *c, size_t i) : ConstLight(c, i),
                                                        modifiableCollection(c)
{
}

glutil::LightSet::Light &glutil::LightSet::Light::SetPosition(const glm::vec3 &pos)
{
    this->modifiableCollection->data[this->id].position = pos;
    this->modifiableCollection->SetDirty();
}

glutil::LightSet::Light &glutil::LightSet::Light::SetType(LightType type)
{
    this->modifiableCollection->data[this->id].type = static_cast<uint32_t>(type);
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetColor(const glm::vec3 &clr)
{
    this->modifiableCollection->data[this->id].color = clr;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetAmbientFactor(float f)
{
    this->modifiableCollection->data[this->id].ambientFactor = f;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LightSet::Light &glutil::LightSet::Light::SetActive(bool active)
{
    this->modifiableCollection->data[this->id].active = active;
    this->modifiableCollection->SetDirty();

    return *this;
}
