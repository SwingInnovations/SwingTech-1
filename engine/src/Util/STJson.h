#ifndef SWINGTECH1_STJSON_H
#define SWINGTECH1_STJSON_H

#include "../../include/json11/json11.hpp"

#include <string>
#include "../STGlobal.h"


//Helps wrap JSON Data
class STJson{
public:

    static Vector2<stReal> FromJson(const std::string& jsonFile){

    }

    static Vector2<stReal> FromJson(const Json doc){
        return Vector2<stReal>::FromJson(doc);
    }

    static std::string ToJson(const Vector2<stReal>& vec) {
        return Json(vec).dump();
    }

    static std::string ToJson(const Vector3<stReal>& vec){
        return Json(vec).dump();
    }

    static std::string ToJson(const Vector4<stReal>& vec){
        return Json(vec).dump();
    }

    static std::string ToJson(const Transform& transform){
        return Json(transform).dump();
    }


};

#endif //SWINGTECH1_STJSON_H
