#pragma once

#include <string>

class OS final {
public:
	static std::string ReadEnvironmentVariable(const char* name);
	static int GetPid();
	static int GetTid();
	static std::string GetCurrentDir();
};

