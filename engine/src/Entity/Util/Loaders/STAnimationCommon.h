#ifndef SWINGTECH1_STANIMATIONCOMMON_H
#define SWINGTECH1_STANIMATIONCOMMON_H

#include <string>
#include <fstream>

#include "../../../Math/STCore.h"
#include "../../../Math/Vector.h"
#include "../../../Application/Util/Data_Structure/STList.h"
#include "../../../Application/Util/File/STSerializeable.h"

struct STVectorKey{
    STVectorKey(){
        m_time = 0.f;
    }

    STVectorKey(stReal time, Vector3D vec){
        m_time = time;
        m_Value = vec;
    }

    void save(std::ofstream& out){
        out.write((char*)&m_time, sizeof(stReal));
        m_Value.save(out);
    }

    void load(std::ifstream& in){
        in.read((char*)&m_time, sizeof(stReal));
        m_Value.load(in);
    }

    stReal m_time;
    Vector3D m_Value;
};

struct STQuaternionKey{
    STQuaternionKey(){

    }

    STQuaternionKey(stReal time, Quaternion value){
        m_time = time;
        m_value = value;
    }

    void save(std::ofstream& out){
        out.write((char*)&m_time, sizeof(stReal));
        m_value.save(out);
    }

    void load(std::ifstream& in){
        in.read((char*)&m_time, sizeof(stReal));
        m_value.load(in);
    }

    stReal m_time;
    Quaternion m_value;
};

struct STNodeAnim{
    std::string name;
    STList<STVectorKey*>        m_positions;
    STList<STQuaternionKey*>    m_rotations;
    STList<STVectorKey*>        m_scalings;

    void save(std::ofstream& out){
        STSerializableUtility::WriteString(name.c_str(), out);
        stUint numPositions, numRotations, numScalings;

        numPositions = m_positions.size();
        numRotations = m_rotations.size();
        numScalings = m_scalings.size();
        out.write((char*)&numPositions, sizeof(stUint));
        out.write((char*)&numRotations, sizeof(stUint));
        out.write((char*)&numScalings, sizeof(stUint));

        for(auto pos : m_positions){
            pos->save(out);
        }
        for(auto rot : m_rotations){
            rot->save(out);
        }
        for(auto scal : m_scalings){
            scal->save(out);
        }
    }

    void load(std::ifstream& in){
        name = STSerializableUtility::ReadString(in);
        stUint numPos, numRot, numScal;
        in.read((char*)&numPos, sizeof(stUint));
        in.read((char*)&numRot, sizeof(stUint));
        in.read((char*)&numScal, sizeof(stUint));
        for(stUint i = 0; i < numPos; i++){
            auto pos = new STVectorKey;
            pos->load(in);
            m_positions.addLast(pos);
        }

        for(stUint i = 0; i < numRot; i++){
            auto rot = new STQuaternionKey;
            rot->load(in);
            m_rotations.addLast(rot);
        }

        for(stUint i = 0; i < numScal; i++){
            auto scal = new STVectorKey;
            scal->load(in);
            m_scalings.addLast(scal);
        }
    }

    ~STNodeAnim(){
        for(auto pos : m_positions) delete pos;
        for(auto rot : m_rotations) delete rot;
        for(auto scale: m_scalings) delete scale;
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

    void save(std::ofstream& out){
        STSerializableUtility::WriteString(name.c_str(), out);
        out.write((char*)&m_Duration, sizeof(stReal));
        out.write((char*)&m_TicksPerSecond, sizeof(stReal));
        stUint numChannels = m_channels.size();
        out.write((char*)&numChannels, sizeof(stUint));
        for(auto chan : m_channels){
            chan->save(out);
        }
    }

    void load(std::ifstream& in){
        stUint numChannels = 0;
        name = STSerializableUtility::ReadString(in);
        in.read((char*)&m_Duration, sizeof(stReal));
        in.read((char*)&m_TicksPerSecond, sizeof(stReal));
        in.read((char*)&numChannels, sizeof(stUint));
        for(stUint i = 0; i < numChannels; i++){
            auto nodeAnim = new STNodeAnim;
            nodeAnim->load(in);
            m_channels.addLast(nodeAnim);
        }
    }
};

#endif //SWINGTECH1_STANIMATIONCOMMON_H
