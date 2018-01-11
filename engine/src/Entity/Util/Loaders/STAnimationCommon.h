#ifndef SWINGTECH1_STANIMATIONCOMMON_H
#define SWINGTECH1_STANIMATIONCOMMON_H

#include <string>

#include "../../../Math/STCore.h"
#include "../../../Math/Vector.h"
#include "../../../Application/Util/Data_Structure/STList.h"

struct STVectorKey{
    STVectorKey(){
        m_time = 0.f;
    }

    STVectorKey(stReal time, Vector3D vec){
        m_time = time;
        m_Value = vec;
    }

    stReal m_time;
    Vector3D m_Value;
    template<class Archive>void serialize(Archive& ar){
        ar(m_time, m_Value);
    }
};

struct STQuaternionKey{
    STQuaternionKey(){

    }

    STQuaternionKey(stReal time, Quaternion value){
        m_time = time;
        m_value = value;
    }

    stReal m_time;
    Quaternion m_value;
    template<class Archive>void serialize(Archive& ar){
        ar(m_time, m_value);
    }
};

struct STNodeAnim{
    std::string name;
    STList<STVectorKey*>        m_positions;
    STList<STQuaternionKey*>    m_rotations;
    STList<STVectorKey*>        m_scalings;
    ~STNodeAnim(){
        for(auto pos : m_positions) delete pos;
        for(auto rot : m_rotations) delete rot;
        for(auto scale: m_scalings) delete scale;
    }
    template<class Archive> void serialize(Archive& ar){
        ar(name);
        //TODO Implement the rest of this;
    }
};

struct STAnimation{
    std::string name;
    stReal m_Duration;
    stReal m_TicksPerSecond;
    STList<STNodeAnim*> m_channels;

    ~STAnimation(){
        for(auto anim : m_channels)delete anim;
    }

    template<class Archive> void serialize(Archive& ar){
        ar(name, m_Duration, m_TicksPerSecond);
    }
};

#endif //SWINGTECH1_STANIMATIONCOMMON_H
