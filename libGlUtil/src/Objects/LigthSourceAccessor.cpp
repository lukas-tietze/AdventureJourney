#include "Objects.hpp"

glutil::LigthSourceCollection::LigthSourceAccessor::LigthSourceAccessor(LigthSourceCollection *c, size_t i) : ConstLigthSourceAccessor(c, i),
                                                                                                              modifiableCollection(c)
{
}

glutil::LigthSourceCollection::LigthSourceAccessor &glutil::LigthSourceCollection::LigthSourceAccessor::SetPosition(const glm::vec3 &pos)
{
    this->collection.data[this->id].position = pos;
    this->modifiableCollection->SetDirty();
}

glutil::LigthSourceCollection::LigthSourceAccessor &glutil::LigthSourceCollection::LigthSourceAccessor::SetType(LigthType type)
{
    this->collection.data[this->id].type = static_cast<uint32_t>(type);
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LigthSourceCollection::LigthSourceAccessor &glutil::LigthSourceCollection::LigthSourceAccessor::SetColor(const glm::vec3 &clr)
{
    this->collection.data[this->id].color = clr;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LigthSourceCollection::LigthSourceAccessor &glutil::LigthSourceCollection::LigthSourceAccessor::SetAmbientFactor(float f)
{
    this->collection.data[this->id].ambienFactor = f;
    this->modifiableCollection->SetDirty();

    return *this;
}

glutil::LigthSourceCollection::LigthSourceAccessor &glutil::LigthSourceCollection::LigthSourceAccessor::SetActive(bool active)
{
    this->collection.data[this->id].active = active;
    this->modifiableCollection->SetDirty();

    return *this;
}
