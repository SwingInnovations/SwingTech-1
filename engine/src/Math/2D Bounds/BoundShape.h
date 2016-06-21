#ifndef WAHOO_BOUNDSHAPE_H
#define WAHOO_BOUNDSHAPE_H

#include <vector>
#include <stdint-gcc.h>
#include "../STCore.h"

class BoundShape{
public:

    virtual bool contains(const BoundShape& other) = 0;
    virtual bool contains(Vector2<stReal>& point) = 0;

    const uint32_t &iterations() const {
        return m_iterations;
    }

    const std::vector<float> &bounds() const {
        return points;
    }

protected:
    std::vector<stReal> points;
    uint32_t m_iterations;
};

#endif //WAHOO_BOUNDSHAPE_H
