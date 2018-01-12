#ifndef SWINGTECH1_STFILEMANAGER_H
#define SWINGTECH1_STFILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/stat.h>

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include "../../../Entity/STEntity.h"
#include "../../../Entity/STActor.h"
/**
 * Wrapper class for file operations.
 */
class STFileManager {
public:
    template<typename T> static bool Write(const std::string& path, T* param);
    template<typename T> static T* Read(const std::string& path);
    template<typename T> static bool WriteEntity(const std::string& path, std::shared_ptr<T> param);
    template<typename T> static std::shared_ptr<T> ReadEntity(const std::string& path);
    static bool DirExists(const std::string& str);
    static int CreateDir(const std::string& filePath);
};

template<typename T>
bool STFileManager::Write(const std::string &path, T *param) {
    std::fstream file(path, std::ios::binary | std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cerr << "Failed to open: " << path << std::endl;
        return false;
    }
    file.write((char*)param, sizeof(T));
    file.flush();
    file.close();
    return true;
}

template<typename T>
T *STFileManager::Read(const std::string &path) {
    T* ret = nullptr;
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::trunc);
    if(!file.is_open()){
        std::cerr << "Failed to open: " << path << std::endl;
        return nullptr;
    }
    file.seekg(0);
    file.read((char*)ret, sizeof(T));
    file.close();
    return ret;
}

template<typename T>
bool STFileManager::WriteEntity(const std::string &path, std::shared_ptr<T> param) {
    if(std::is_base_of<STEntity, T>::value ){
        std::stringstream ss;
        cereal::BinaryOutputArchive outputArchive(ss);
        outputArchive(param);
        std::ofstream out(path);
        out << ss.rdbuf();
        out.close();
        return true;
    }
    std::cerr << "Provided type is not of base STEntity" << std::endl;
    return false;
}

template<typename T>
std::shared_ptr<T> STFileManager::ReadEntity(const std::string &path) {
    if(std::is_base_of<STEntity, T>::value) {
        std::ifstream inFile(path);
        if(inFile){
            auto ret = std::make_shared<T>();
            std::stringstream ss;
            ss << inFile.rdbuf();
            inFile.close()
                    ;
            cereal::BinaryInputArchive inputArchive(ss);
            inputArchive(ret);
            ret->ReloadFromSave();
            return ret;
        }
        std::cerr << "Failed to read: " << path << std::endl;
        return nullptr;
    }
    std::cerr << "Provided Template type is not of base STEntity...Loading failed" << std::endl;
    return nullptr;
}


#endif //SWINGTECH1_STFILEMANAGER_H
