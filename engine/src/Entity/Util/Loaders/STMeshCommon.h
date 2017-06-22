#ifndef SWINGTECH1_STMESHCOMMON_H
#define SWINGTECH1_STMESHCOMMON_H

#include <vector>
#include "../../../Math/STCore.h"
#include "../../../Math/Vector.h"
#include "../../../Math/Vertex.h"

/**
 * @brief Common Mesh Structure
 */
struct STMesh_Structure{
    std::string name;
    std::string materialKey;
    Vector3<stReal> m_minPt;
    Vector3<stReal> m_maxPt;
    std::vector<int> m_indices;
    std::vector<Vertex> m_vertices;

    Vertex* getVertices(){ return &m_vertices[0]; }
    int* getIndicies(){ return &m_indices[0]; }

    inline stInt getVertexSize()const { return (stInt)m_vertices.size(); }
    inline stInt getIndexSize() const { return (stInt)m_indices.size(); }
};

#endif //SWINGTECH1_STMESHCOMMON_H
