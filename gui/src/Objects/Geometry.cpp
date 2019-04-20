#include "Objects.hpp"
#include "data/Io.hpp"

glutil::Geometry::Geometry(const Mesh &mesh)
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetVertexDataSize(), mesh.GetVertexData(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexDataSize(), mesh.GetIndexData(), GL_STATIC_DRAW);

    util::dbg.WriteLine("Created Geometry [%]: vertices: %*%=%Bytes, indices: %*%=%Bytes, vao=%, vbo=%, ibo=%",
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

        util::dbg.WriteLine("Created Atribute % for Geometry [%]: count=% type=%, normalized=%, stride=%, offset=%",
                            attribute.GetIndex(),
                            this,
                            attribute.GetCount(),
                            attribute.GetType(),
                            attribute.IsNormalized(),
                            mesh.GetVertexSize(),
                            attribute.GetOffset());
    }
}

glutil::Geometry::Geometry(const std::vector<Mesh *> &meshes)
{
}

glutil::Geometry::Geometry(const Mesh *, size_t count)
{
}

glutil::Geometry::~Geometry()
{
    glDeleteVertexArrays(1, &this->vao);
    this->vao = 0;

    glDeleteBuffers(1, &this->vbo);
    this->vbo = 0;

    glDeleteBuffers(1, &this->ibo);
    this->ibo = 0;
}

void glutil::Geometry::Bind()
{
    glBindVertexArray(this->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
