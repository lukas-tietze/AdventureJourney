#include "Objects.hpp"

glutil::Mesh::Mesh() : vertexCount(0),
                       indexCount(0),
                       vertexSize(0),
                       indexSize(0),
                       attributes(0),
                       vertices(nullptr),
                       indices(nullptr),
                       dataManaged(false)
{
}

glutil::Mesh::~Mesh()
{
    this->Discard();
}

bool glutil::Mesh::LoadFromData(int vertexCount, int vertexSize, void *vertices, int indexCount, int indexSize, void *indices, std::vector<GeometryBufferAttribute> attributes, bool managaData)
{
    this->vertexCount = vertexCount;
    this->indexCount = indexCount;
    this->vertexSize = vertexSize;
    this->indexSize = indexSize;
    this->attributes = attributes;
    this->vertices = vertices;
    this->indices = indices;
    this->dataManaged = managaData;

    return true;
}

void glutil::Mesh::Discard()
{
    this->vertexCount = 0;
    this->indexCount = 0;
    this->vertexSize = 0;
    this->indexSize = 0;
    this->attributes.clear();

    if (this->dataManaged)
    {
        delete[] this->vertices;
        delete[] this->indices;
    }

    this->vertices = nullptr;
    this->indices = nullptr;
};

int glutil::Mesh::GetVertexCount() const
{
    return this->vertexCount;
}

int glutil::Mesh::GetIndexCount() const
{
    return this->indexCount;
}

int glutil::Mesh::GetVertexSize() const
{
    return this->vertexSize;
}

int glutil::Mesh::GetIndexSize() const
{
    return this->indexSize;
}

int glutil::Mesh::GetVertexDataSize() const
{
    return this->vertexCount * this->vertexSize;
}

int glutil::Mesh::GetIndexDataSize() const
{
    return this->indexCount * this->indexSize;
}

const void *glutil::Mesh::GetVertexData() const
{
    return this->vertices;
}

const void *glutil::Mesh::GetIndexData() const
{
    return this->indices;
}

const std::vector<glutil::GeometryBufferAttribute> &glutil::Mesh::GetAttributes() const
{
    return this->attributes;
}