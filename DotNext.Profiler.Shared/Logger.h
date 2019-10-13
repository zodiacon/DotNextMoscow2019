#pragma once

#include <fstream>
#include "Mutex.h"
#include "AutoLock.h"


enum class LogLevel {
	Verbose,
	Debug,
	Info,
	Warning,
	Error,
	Fatal
};

class Logger final {
public:
	Logger();

	static Logger& Get();
	static void Shutdown();

	LogLevel GetLevel() const;
	void SetLevel(LogLevel level);

	template<typename... Args>
	void Log(LogLevel level, Args&&... args) {
		if (level > _level)
			return;

		AutoLock locker(_lock);
		char buffer[1 << 10];
#ifdef _WINDOWS
		sprintf_s(buffer, args...);
#else
		sprintf(buffer, args...);
#endif
		_file << buffer << std::endl;

	}
	template<typename... Args>
	static void Info(Args&&... args) {
		Get().Log(LogLevel::Info, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Error(Args&&... args) {
		Get().Log(LogLevel::Error, std::forward<Args>(args)...);
	}

	template<typename... Args>
	static void Warning(Args&&... args) {
		Get().Log(LogLevel::Warning, std::forward<Args>(args)...);
	}

private:
	Mutex _lock;
	std::ofstream _file;
	LogLevel _level = LogLevel::Info;
};

