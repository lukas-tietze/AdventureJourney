#include "Objects.hpp"

glutil::GeometryBufferAttribute::GeometryBufferAttribute() : index(0),
                                                             type(0),
                                                             count(0),
                                                             offset(0),
                                                             normalized(false)
{
}

glutil::GeometryBufferAttribute::GeometryBufferAttribute(int index, int count, int type, bool normalized, int offset) : index(index),
                                                                                                                        type(type),
                                                                                                                        count(count),
                                                                                                                        offset(offset),
                                                                                                                        normalized(normalized)
{
}

int glutil::GeometryBufferAttribute::GetIndex() const
{
    return this->index;
}

int glutil::GeometryBufferAttribute::GetType() const
{
    return this->type;
}

int glutil::GeometryBufferAttribute::GetCount() const
{
    return this->count;
}

int glutil::GeometryBufferAttribute::GetOffset() const
{
    return this->offset;
}

bool glutil::GeometryBufferAttribute::IsNormalized() const
{
    return this->normalized;
}