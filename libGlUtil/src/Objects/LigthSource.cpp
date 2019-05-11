#include "Objects.hpp"

glutil::LigthSource::LigthSource()
{
}

glutil::LigthSource::LigthSource(const glm::vec3 &position, bool directionalLigth, const glm::vec3 &color, float ambientFactor, bool active)
{
}

const glm::vec3 &glutil::LigthSource::GetPosition() const
{
    return this->data.position;
}

glutil::LigthType glutil::LigthSource::GetType() const
{
    return static_cast<LigthType>(this->data.type);
}

const glm::vec3 &glutil::LigthSource::GetColor() const
{
    return this->data.color;
}

float glutil::LigthSource::GetAmbientFactor() const
{
    return this->data.ambienFactor;
}

bool glutil::LigthSource::IsActive() const
{
    return this->data.active;
}

void glutil::LigthSource::SetPosition(const glm::vec3 &pos)
{
    this->data.position = pos;
    this->SetDirty();
}

void glutil::LigthSource::SetType(LigthType type)
{
    this->data.type = static_cast<uint32_t>(type);
    this->SetDirty();
}

void glutil::LigthSource::SetColor(const glm::vec3 &clr)
{
    this->data.color = clr;
}

void glutil::LigthSource::SetAmbientFactor(float f)
{
    this->data.ambienFactor = f;
}

void glutil::LigthSource::SetActive(bool active)
{
    this->data.active = active;
}
