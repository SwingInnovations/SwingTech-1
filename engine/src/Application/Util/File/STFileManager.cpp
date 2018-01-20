#include <sys/types.h>
#include "STFileManager.h"

bool STFileManager::DirExists(const std::string &str) {
    struct stat info;
    if(stat(str.c_str(), &info) != 0) return false;
    else if(info.st_mode & S_IFDIR) return true;
    return false;
}

int STFileManager::CreateDir(const std::string &filePath) {
#if __MINGW32__
    return mkdir(filePath.c_str());
#elif __linux__
    return mkdir(filePath.c_str(), S_IFDIR);
#else
	return 0;
#endif
}
