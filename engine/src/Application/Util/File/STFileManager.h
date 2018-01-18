#ifndef SWINGTECH1_STFILEMANAGER_H
#define SWINGTECH1_STFILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/stat.h>


#include "../../../Entity/STEntity.h"
#include "../../../Entity/STActor.h"
/**
 * Wrapper class for file operations.
 */
class STFileManager {
public:
    template<typename T> static bool Write(const std::string& path, T* param);
    template<typename T> static T* Read(const std::string& path);
    static bool DirExists(const std::string& str);
    static int CreateDir(const std::string& filePath);
};

template<typename T>
bool STFileManager::Write(const std::string &path, T *param) {
    std::ofstream file(path, std::ios::binary | std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cerr << "Failed to open: " << path << std::endl;
        return false;
    }
    param->save(file);
    file.flush();
    file.close();
    return true;
}

template<typename T>
T *STFileManager::Read(const std::string &path) {
    T* ret = new T();
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if(!file.is_open()){
        std::cerr << "Failed to open: " << path << std::endl;
        return nullptr;
    }
    ret->load(file);
    file.close();
    return ret;
}


#endif //SWINGTECH1_STFILEMANAGER_H
