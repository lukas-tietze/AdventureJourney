#include "Objects.hpp"

glutil::LigthSourceCollection::ConstLigthSourceAccessor::ConstLigthSourceAccessor(const LigthSourceCollection *parent, size_t index) : collection(parent),
                                                                                                                                       id(index)
{
}

const glm::vec3 &glutil::LigthSourceCollection::ConstLigthSourceAccessor::GetPosition() const
{
    return this->collection.data[this->id].position;
}

glutil::LigthType glutil::LigthSourceCollection::ConstLigthSourceAccessor::GetType() const
{
    return static_cast<LigthType>(this->collection.data[this->id].type);
}

const glm::vec3 &glutil::LigthSourceCollection::ConstLigthSourceAccessor::GetColor() const
{
    return this->collection.data[this->id].color;
}

float glutil::LigthSourceCollection::ConstLigthSourceAccessor::GetAmbientFactor() const
{
    return this->collection.data[this->id].ambienFactor;
}

bool glutil::LigthSourceCollection::ConstLigthSourceAccessor::IsActive() const
{
    return this->collection.data[this->id].active;
}