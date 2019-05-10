#include "Objects.hpp"

glutil::Material::Material()
{
}

glutil::Material::Material(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, float shininess)
{
    this->data.ambientColor = ambient;
    this->data.diffuseColor = diffuse;
    this->data.specularColor = specular;
    this->data.shininess = shininess;

    this->SetDirty();
}