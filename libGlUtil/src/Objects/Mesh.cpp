#include "Objects.hpp"
#include "data/Io.hpp"
#include "GlUtils.hpp"

glutil::Mesh::Mesh() : vao(0),
                       vbo(0),
                       ibo(0),
                       indexCount(0),
                       drawMode(0),
                       indexType(0)
{
}

glutil::Mesh::Mesh(const MeshBuffer &meshBuffer) : Mesh()
{
    this->LoadFromBuffer(meshBuffer);
}

glutil::Mesh::Mesh(Mesh &&mesh) : Mesh()
{
    this->TransferFrom(mesh);
}

glutil::Mesh::~Mesh()
{
    this->DestroyGlObjects();
}

void glutil::Mesh::DestroyGlObjects()
{
    if (this->vao)
    {
        util::dbg.WriteLine("Deleting vao % of geometry buffer [%]", this->vao, this);
        glDeleteVertexArrays(1, &this->vao);
        this->vao = 0;
    }

    if (this->vbo)
    {
        util::dbg.WriteLine("Deleting vbo % of geometry buffer [%]", this->vbo, this);
        glDeleteBuffers(1, &this->vbo);
        this->vbo = 0;
    }

    if (this->ibo)
    {
        util::dbg.WriteLine("Deleting ibo % of geometry buffer [%]", this->ibo, this);
        glDeleteBuffers(1, &this->ibo);
        this->ibo = 0;
    }
}

void glutil::Mesh::TransferFrom(Mesh &mesh)
{
    this->vao = mesh.vao;
    this->vbo = mesh.vbo;
    this->ibo = mesh.ibo;
    this->indexCount = mesh.indexCount;
    this->drawMode = mesh.drawMode;
    this->indexType = mesh.indexType;

    mesh.vao = 0;
    mesh.vbo = 0;
    mesh.ibo = 0;
    mesh.indexCount = 0;
    mesh.drawMode = 0;
    mesh.indexType = 0;
}

void glutil::Mesh::LoadFromBuffer(const MeshBuffer &mesh)
{
    this->DestroyGlObjects();

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetVertexDataSize(), mesh.GetVertexData(), GL_STATIC_DRAW);

    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexDataSize(), mesh.GetIndexData(), GL_STATIC_DRAW);

    this->indexCount = mesh.GetIndexCount();
    this->drawMode = mesh.GetDrawMode();
    this->indexType = mesh.GetIndexType();

    util::dbg.WriteLine("Created Mesh [%]: vertices: %*%=%Bytes, indices: %*%=%Bytes, drawMode=%, indexCount=%, indexType=%, vao=%, vbo=%, ibo=%",
                        this,
                        mesh.GetVertexCount(),
                        mesh.GetVertexSize(),
                        mesh.GetVertexDataSize(),
                        mesh.GetIndexCount(),
                        mesh.GetIndexSize(),
                        mesh.GetIndexDataSize(),
                        this->drawMode,
                        this->indexCount,
                        this->indexType,
                        this->vao,
                        this->vbo,
                        this->ibo);

    for (const auto &attribute : mesh.GetAttributes())
    {
        glVertexAttribPointer(attribute.GetIndex(),
                              attribute.GetCount(),
                              attribute.GetType(),
                              attribute.IsNormalized(),
                              mesh.GetVertexSize(),
                              (void *)attribute.GetOffset());
        glEnableVertexAttribArray(attribute.GetIndex());

        util::dbg.WriteLine("Created Atribute % for Mesh [%]: count=% type=%, normalized=%, stride=%, offset=%",
                            attribute.GetIndex(),
                            this,
                            attribute.GetCount(),
                            attribute.GetType(),
                            attribute.IsNormalized(),
                            mesh.GetVertexSize(),
                            attribute.GetOffset());
    }
}

bool glutil::Mesh::LoadFromJson(const std::string &path)
{
    MeshBuffer buf;

    buf.LoadFromJson(path);

    this->LoadFromBuffer(buf);
}

bool glutil::Mesh::LoadFromCg2vd(const std::string &path)
{
    MeshBuffer buf;

    buf.LoadFromCg2vd(path);

    this->LoadFromBuffer(buf);
}

bool glutil::Mesh::LoadFromData(int vertexCount, int vertexSize, void *vertices,
                                int indexCount, int indexType, void *indices,
                                std::vector<MeshAttribute> attributes,
                                int drawMode, bool managaData)
{
    MeshBuffer buf;

    buf.LoadFromData(vertexCount, vertexSize, vertices,
                     indexCount, indexType, indices,
                     attributes, drawMode, managaData);

    this->LoadFromBuffer(buf);
}

void glutil::Mesh::Draw()
{
    glBindVertexArray(this->vao);
    glDrawElements(this->drawMode, this->indexCount, this->indexType, nullptr);
}

glutil::Mesh &glutil::Mesh::operator=(Mesh &&mesh)
{
    this->TransferFrom(mesh);

    return *this;
}