#include "QuadricHelper.internal.hpp"

void AddTriangle(float x0, float y0, float z0, float nx0, float ny0, float nz0,
                 float x1, float y1, float z1, float nx1, float ny1, float nz1,
                 float x2, float y2, float z2, float nx2, float ny2, float nz2)
{
    // 	// Increase array storage by 3 vertices.
    // 	m_positions = (float*)realloc(m_positions, sizeof(float) * 3 * (m_vertexCount + 3));
    // 	m_normals = (float*)realloc(m_normals, sizeof(float) * 3 * (m_vertexCount + 3));
    // 	m_colors = (float*)realloc(m_colors, sizeof(float) * 4 * (m_vertexCount + 3));
    // 	m_texcoords = (float*)realloc(m_texcoords, sizeof(float) * 2 * (m_vertexCount + 3));

    // 	// Get the next free array position.
    // 	float *p = m_positions + 3 * m_vertexCount,
    // 		*n = m_normals + 3 * m_vertexCount,
    // 		*c = m_colors + 4 * m_vertexCount,
    // 		*t = m_texcoords + 2 * m_vertexCount;

    // 	// Set the respective values.
    // #define SET2(pos,x,y)     { (pos)[0]=x; (pos)[1]=y;                     }
    // #define SET3(pos,x,y,z)   { (pos)[0]=x; (pos)[1]=y; (pos)[2]=z;           }
    // 	SET3(p + 0, x0, y0, z0) SET3(n + 0, nx0, ny0, nz0) SET2(t + 0, 0, 0) memcpy(c + 0, m_standardRGBA, sizeof(float) * 4);
    // 	SET3(p + 3, x1, y1, z1) SET3(n + 3, nx1, ny1, nz1) SET2(t + 2, 0, 0) memcpy(c + 4, m_standardRGBA, sizeof(float) * 4);
    // 	SET3(p + 6, x2, y2, z2) SET3(n + 6, nx2, ny2, nz2) SET2(t + 4, 0, 0) memcpy(c + 8, m_standardRGBA, sizeof(float) * 4);
    // #undef SET2
    // #undef SET3

    // 	// Increase internal vertex count.
    // 	m_vertexCount += 3;
}

void AddQuad(float x0, float y0, float z0, float nx0, float ny0, float nz0,
             float x1, float y1, float z1, float nx1, float ny1, float nz1,
             float x2, float y2, float z2, float nx2, float ny2, float nz2,
             float x3, float y3, float z3, float nx3, float ny3, float nz3)
{
    AddTriangle(x0, y0, z0, nx0, ny0, nz0,
                x1, y1, z1, nx1, ny1, nz1,
                x2, y2, z2, nx2, ny2, nz2);
    AddTriangle(x0, y0, z0, nx0, ny0, nz0,
                x2, y2, z2, nx2, ny2, nz2,
                x3, y3, z3, nx3, ny3, nz3);
}