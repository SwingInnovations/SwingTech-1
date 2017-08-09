#ifndef SWINGTECH1_STFILEMANAGER_H
#define SWINGTECH1_STFILEMANAGER_H


#include <string>
#include <sys/stat.h>

/**
 * Wrapper class for file operations.
 */
class STFileManager {
public:
    static bool DirExists(const std::string& str);
    static int CreateDir(const std::string& filePath);
};


#endif //SWINGTECH1_STFILEMANAGER_H
