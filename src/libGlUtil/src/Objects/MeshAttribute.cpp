#include "Objects.hpp"

glutil::MeshAttribute::MeshAttribute() : index(0),
                                                             type(0),
                                                             count(0),
                                                             offset(0),
                                                             normalized(false)
{
}

glutil::MeshAttribute::MeshAttribute(int index, int count, int type, bool normalized, int offset) : index(index),
                                                                                                                        type(type),
                                                                                                                        count(count),
                                                                                                                        offset(offset),
                                                                                                                        normalized(normalized)
{
}

int glutil::MeshAttribute::GetIndex() const
{
    return this->index;
}

int glutil::MeshAttribute::GetType() const
{
    return this->type;
}

int glutil::MeshAttribute::GetCount() const
{
    return this->count;
}

int glutil::MeshAttribute::GetOffset() const
{
    return this->offset;
}

bool glutil::MeshAttribute::IsNormalized() const
{
    return this->normalized;
}