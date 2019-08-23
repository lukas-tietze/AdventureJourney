#include "Objects.hpp"
#include "data/Io.hpp"
#include "Exception.hpp"
#include <cstring>

glutil::MeshBuffer::MeshBuffer() : vertexCount(0),
                                   indexCount(0),
                                   vertexSize(0),
                                   indexSize(0),
                                   indexType(0),
                                   attributes(0),
                                   vertices(nullptr),
                                   indices(nullptr),
                                   drawMode(0),
                                   dataManaged(false)
{
}

glutil::MeshBuffer::MeshBuffer(const MeshBuffer &mesh)
{
    this->CopyFrom(mesh);
}

glutil::MeshBuffer::MeshBuffer(MeshBuffer &&mesh)
{
    this->TransferFrom(mesh);
}

glutil::MeshBuffer::~MeshBuffer()
{
    util::dbg.WriteLine("Destroying MeshBuffer [%]", this);

    this->vertexCount = 0;
    this->vertexSize = 0;
    this->indexCount = 0;
    this->indexSize = 0;
    this->indexType = 0;

    this->attributes.clear();

    if (this->dataManaged)
    {
        util::dbg.WriteLine("Deleting data of MeshBuffer [%]", this);

        delete[] this->vertices;
        delete[] this->indices;
    }

    this->vertices = nullptr;
    this->indices = nullptr;

    this->drawMode = 0;
}

void glutil::MeshBuffer::CopyFrom(const MeshBuffer &mesh)
{
    this->vertexCount = mesh.vertexCount;
    this->indexCount = mesh.indexCount;
    this->vertexSize = mesh.vertexSize;
    this->indexSize = mesh.indexSize;
    this->indexType = mesh.indexType;
    this->attributes = mesh.attributes;
    this->drawMode = mesh.drawMode;

    if (mesh.dataManaged)
    {
        util::dbg.WriteLine("Created MeshBuffer % from deep copy of %.", this, &mesh);

        this->vertices = new uint8_t[mesh.GetVertexDataSize()];
        this->indices = new uint8_t[mesh.GetIndexDataSize()];
        this->dataManaged = true;

        std::memcpy(this->vertices, mesh.vertices, mesh.GetVertexDataSize());
        std::memcpy(this->indices, mesh.indices, mesh.GetIndexDataSize());
    }
    else
    {
        util::dbg.WriteLine("Created MeshBuffer % from shallow copy of %.", this, &mesh);

        this->vertices = mesh.vertices;
        this->indices = mesh.indices;
        this->dataManaged = false;
    }
}

void glutil::MeshBuffer::TransferFrom(MeshBuffer &mesh)
{
    this->vertexCount = mesh.vertexCount;
    this->indexCount = mesh.indexCount;
    this->vertexSize = mesh.vertexSize;
    this->indexSize = mesh.indexSize;
    this->indexType = mesh.indexType;
    this->attributes = mesh.attributes;
    this->drawMode = mesh.drawMode;
    this->vertices = mesh.vertices;
    this->indices = mesh.indices;
    this->dataManaged = mesh.dataManaged;

    mesh.vertexCount = 0;
    mesh.indexCount = 0;
    mesh.vertexSize = 0;
    mesh.indexSize = 0;
    mesh.indexType = 0;
    mesh.attributes.clear();
    mesh.drawMode = 0;
    mesh.vertices = nullptr;
    mesh.vertices = nullptr;
    mesh.dataManaged = false;

    util::dbg.WriteLine("Created MeshBuffer % from transfer of %.", this, &mesh);
}

int glutil::MeshBuffer::CalculateIndexSize(int type)
{
    switch (type)
    {
    case GL_UNSIGNED_BYTE:
        return sizeof(GLubyte);
    case GL_UNSIGNED_SHORT:
        return sizeof(GLushort);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    default:
        throw util::InvalidCaseException();
    }
}

bool glutil::MeshBuffer::LoadFromData(int vertexCount, int vertexSize, void *vertices, int indexCount, int indexType, void *indices, std::vector<MeshAttribute> attributes, int drawMode, bool managaData)
{
    this->vertexCount = vertexCount;
    this->vertexSize = vertexSize;
    this->indexCount = indexCount;
    this->indexType = indexType;
    this->indexSize = this->CalculateIndexSize(indexType);
    this->attributes = attributes;
    this->drawMode = drawMode;
    this->dataManaged = managaData;

    if (this->dataManaged)
    {
        this->vertices = new uint8_t[this->vertexCount * this->vertexSize];
        this->indices = new uint8_t[this->indexCount * this->indexSize];

        std::memcpy(this->vertices, vertices, this->vertexCount * this->vertexSize * sizeof(uint8_t));
        std::memcpy(this->indices, indices, this->indexCount * this->indexSize * sizeof(uint8_t));
    }
    else
    {
        this->vertices = vertices;
        this->indices = indices;
    }

    util::dbg.WriteLine("Loaded MeshBuffer [%] from data: vertexCount=%, vertexSize=%, indexCount=%, indexType=%, indexSize=%, drawMode=%, attributes=%, dataManaged=%",
                        this,
                        this->vertexCount,
                        this->vertexSize,
                        this->indexCount,
                        this->indexType,
                        this->indexSize,
                        this->drawMode,
                        attributes.size(),
                        this->dataManaged);

    for (const auto &attrib : this->attributes)
    {
        util::dbg.WriteLine("Loaded Attribute % for MeshBuffer [%]: count=%, type=%, normalized=%, offset=%",
                            attrib.GetIndex(),
                            this,
                            attrib.GetCount(),
                            attrib.GetType(),
                            attrib.IsNormalized(),
                            attrib.GetOffset());
    }

    return true;
}

int glutil::MeshBuffer::GetVertexCount() const
{
    return this->vertexCount;
}

int glutil::MeshBuffer::GetVertexSize() const
{
    return this->vertexSize;
}

int glutil::MeshBuffer::GetVertexDataSize() const
{
    return this->vertexCount * this->vertexSize;
}

const void *glutil::MeshBuffer::GetVertexData() const
{
    return this->vertices;
}

int glutil::MeshBuffer::GetIndexCount() const
{
    return this->indexCount;
}

int glutil::MeshBuffer::GetIndexSize() const
{
    return this->indexSize;
}

int glutil::MeshBuffer::GetIndexType() const
{
    return this->indexType;
}

int glutil::MeshBuffer::GetIndexDataSize() const
{
    return this->indexCount * this->indexSize;
}

const void *glutil::MeshBuffer::GetIndexData() const
{
    return this->indices;
}

int glutil::MeshBuffer::GetDrawMode() const
{
    return this->drawMode;
}

const std::vector<glutil::MeshAttribute> &glutil::MeshBuffer::GetAttributes() const
{
    return this->attributes;
}

const glutil::MeshBuffer &glutil::MeshBuffer::operator=(const MeshBuffer &mesh)
{
    this->CopyFrom(mesh);

    return *this;
}

glutil::MeshBuffer &glutil::MeshBuffer::operator=(MeshBuffer &&mesh)
{
    this->TransferFrom(mesh);

    return *this;
}
