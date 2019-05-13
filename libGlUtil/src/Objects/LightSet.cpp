#include "Objects.hpp"

glutil::LightSet::Light glutil::LightSet::Add()
{
    this->data.push_back(LightSourceUboData());
    
    this->Resize();

    return Light(this, this->data.size() - 1);
}

size_t glutil::LightSet::Size() const
{
    return this->data.size();
}

void glutil::LightSet::Clear()
{
    this->data.clear();
}

glutil::LightSet::Light glutil::LightSet::operator[](size_t i)
{
    return Light(this, i);
}

glutil::LightSet::ConstLight glutil::LightSet::operator[](size_t i) const
{
    return ConstLight(this, i);
}
