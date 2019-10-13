#include "Logger.h"
#include "OS.h"

Logger& Logger::Get() {
	static Logger logger;
	return logger;
}

void Logger::Shutdown() {
	Get()._file.close();
}

Logger::Logger() {
	auto logDir = OS::ReadEnvironmentVariable("DotNext_LogDir");
	//if (logDir.empty())
	//	logDir = OS::GetCurrentDir();
	
}
