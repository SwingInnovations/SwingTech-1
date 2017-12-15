#ifndef SWINGTECH1_EULER_H
#define SWINGTECH1_EULER_H

template<class T>
class Euler{
public:
    /** Default Euler Constructor
     *
     * @return
     */
    Euler(){
        m_val[0] = 0;
        m_val[1] = 0;
        m_val[2] = 0;
    }

    /** Euler Constructor
     *
     * @param _x    x Component
     * @param _y    Y Component
     * @param _z    Z Component
     * @return
     */
    Euler(const T &_x, const T &_y, const T &_z) {
        m_val[0] = _x;
        m_val[1] = _y;
        m_val[2] = _z;
    }

    /** Sets Euler components from Vector3 componenets.
     *
     * @param other
     */
    inline void set(const Vector3<stReal> other){
        m_val[0] = (T)other.getX();
        m_val[1] = (T)other.getY();
        m_val[2] = (T)other.getZ();
    }

    inline void setX(const T& _x){ m_val[0] = _x; }
    inline void setY(const T& _y){ m_val[1] = _y; }
    inline void setZ(const T& _z){ m_val[2] = _z; }

    inline T getX()const{ return m_val[0]; }
    inline T getY()const{ return m_val[1]; }
    inline T getZ()const{ return m_val[2]; }

private:
    T m_val[3];
};

typedef Euler<stReal> Euler3D;

#endif //SWINGTECH1_EULER_H
