#ifndef WAHOO_BOUNDSHAPE_H
#define WAHOO_BOUNDSHAPE_H

#include <vector>
#include "../STCore.h"

class BoundShape{
public:

    virtual bool contains(const BoundShape& other) = 0;
    virtual bool contains(const Vector2<stReal> &point) = 0;

    const unsigned int &iterations() const {
        return m_iterations;
    }

    const std::vector<float> &bounds() const {
        return points;
    }

protected:
    std::vector<stReal> points;
    unsigned int m_iterations;
};

#endif //WAHOO_BOUNDSHAPE_H
