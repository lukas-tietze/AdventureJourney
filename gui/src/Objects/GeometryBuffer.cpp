#include "Objects.hpp"
#include "data/Io.hpp"

glutil::GeometryBuffer::GeometryBuffer() : vao(0),
                                           vbo(0),
                                           ibo(0)
{
}

glutil::GeometryBuffer::GeometryBuffer(const Mesh &mesh)
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetVertexDataSize(), mesh.GetVertexData(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexDataSize(), mesh.GetIndexData(), GL_STATIC_DRAW);

    util::dbg.WriteLine("Created GeometryBuffer [%]: vertices: %*%=%Bytes, indices: %*%=%Bytes, vao=%, vbo=%, ibo=%",
                        this,
                        mesh.GetVertexCount(),
                        mesh.GetVertexSize(),
                        mesh.GetVertexDataSize(),
                        mesh.GetIndexCount(),
                        mesh.GetIndexSize(),
                        mesh.GetIndexDataSize(),
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

        util::dbg.WriteLine("Created Atribute % for GeometryBuffer [%]: count=% type=%, normalized=%, stride=%, offset=%",
                            attribute.GetIndex(),
                            this,
                            attribute.GetCount(),
                            attribute.GetType(),
                            attribute.IsNormalized(),
                            mesh.GetVertexSize(),
                            attribute.GetOffset());
    }
}

glutil::GeometryBuffer::~GeometryBuffer()
{
    util::dbg.WriteLine("Destroying geometry buffer [%]", this);

    util::dbg.WriteLine("Deleting vao % of geometry buffer [%]", this->vao, this);
    glDeleteVertexArrays(1, &this->vao);
    this->vao = 0;

    util::dbg.WriteLine("Deleting vbo % of geometry buffer [%]", this->vbo, this);
    glDeleteBuffers(1, &this->vbo);
    this->vbo = 0;

    util::dbg.WriteLine("Deleting ibo % of geometry buffer [%]", this->ibo, this);
    glDeleteBuffers(1, &this->ibo);
    this->ibo = 0;
}

bool glutil::GeometryBuffer::Buffer(const glutil::Mesh &, glutil::SceneObject &)
{
}

void glutil::GeometryBuffer::Bind()
{
    glBindVertexArray(this->vao);
}
