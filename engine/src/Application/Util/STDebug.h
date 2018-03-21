
#include <string>
#include <iostream>
#if _MSC_VER > 1900
#include <Windows.h>
#endif

class STDebug {
public:
	static void Log(const std::string& output) {
#if _MSC_VER > 1900
		OutputDebugString((output + "\n").c_str());
#else
		//std::cout << output << std::end;
#endif
	}

	static void LogError(const std::string& output) {
#if _MSC_VER > 1900
		OutputDebugString((output + "\n").c_str());
#else
		//std::cerr << output << std::endl;
#endif
	}
};