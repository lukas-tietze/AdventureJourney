#include "Objects.hpp"

glutil::Material::Material() : albedoMap(nullptr),
                               albedoMapTarget(0),
                               normalMap(nullptr),
                               normalMapTarget(0),
                               propertyMap(nullptr),
                               propertyMapTarget(0)
{
}

void glutil::Material::SetAlbedo(const glm::vec4 &albedo)
{
    if (this->data.albedo != albedo)
    {
        this->data.albedo = albedo;
        this->SetDirty();
    }
}

void glutil::Material::SetShininess(float s)
{
    if (this->data.shininess_metalness.x != s)
    {
        this->data.shininess_metalness.x = s;
        this->SetDirty();
    }
}

void glutil::Material::SetMetalness(float m)
{
    if (this->data.shininess_metalness.y != m)
    {
        this->data.shininess_metalness.y = m;
        this->SetDirty();
    }
}

void glutil::Material::SetNormalMap(Texture *map, GLenum target)
{
    this->normalMap = map;
    this->normalMapTarget = target;
}

void glutil::Material::SetAlbedoMap(Texture *map, GLenum target)
{
    this->albedoMap = map;
    this->albedoMapTarget = target;
}

void glutil::Material::SetPropertyMap(Texture *map, GLenum target)
{
    this->propertyMap = map;
    this->propertyMapTarget = target;
}

const glm::vec4 &glutil::Material::GetAlbedo(const glm::vec4 &) const
{
    return this->data.albedo;
}

float glutil::Material::GetShininess(float) const
{
    return this->data.shininess_metalness.x;
}

float glutil::Material::GetMetalness(float) const
{
    return this->data.shininess_metalness.y;
}

void glutil::Material::Use()
{
    this->Bind();
    this->Upload();

    if (this->albedoMap)
        this->albedoMap->Bind(this->albedoMapTarget);

    if (this->normalMap)
        this->normalMap->Bind(this->normalMapTarget);

    if (this->propertyMap)
        this->propertyMap->Bind(this->propertyMapTarget);
}