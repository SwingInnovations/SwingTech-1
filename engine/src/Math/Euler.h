#ifndef SWINGTECH1_EULER_H
#define SWINGTECH1_EULER_H

template<class T>
class Euler{
public:
    Euler(){
        m_val[0] = 0;
        m_val[1] = 0;
        m_val[2] = 0;
    }

    Euler(const T &_x, const T &_y, const T &_z) {
        m_val[0] = _x;
        m_val[1] = _y;
        m_val[2] = _z;
    }

    void setX(const T& _x){ m_val[0] = _x; }
    void setY(const T& _y){ m_val[1] = _y; }
    void setZ(const T& _z){ m_val[2] = _z; }

    T getX()const{ return m_val[0]; }
    T getY()const{ return m_val[1]; }
    T getZ()const{ return m_val[2]; }

private:
    T m_val[3];
};

#endif //SWINGTECH1_EULER_H
