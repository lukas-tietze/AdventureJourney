#include "Objects.hpp"

glutil::LigthSourceCollection::LigthSourceCollection()
{
}

void glutil::LigthSourceCollection::Add(size_t n)
{
    for (int i = 0; i < n; i++)
        this->data.push_back(LigthSourceUboData());
}

size_t glutil::LigthSourceCollection::Size() const
{
    return this->data.size();
}

void glutil::LigthSourceCollection::Clear()
{
}

glutil::LigthSourceCollection::LigthSourceAccessor glutil::LigthSourceCollection::operator[](size_t i)
{
    return LigthSourceAccessor(this, i);
}

glutil::LigthSourceCollection::LigthSourceAccessor glutil::LigthSourceCollection::operator[](size_t i) const
{
    return ConstLigthSourceAccessor(this, i); 
}
