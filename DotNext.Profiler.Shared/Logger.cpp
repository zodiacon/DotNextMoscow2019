#include "Logger.h"
#include "OS.h"
#include <sstream>
#include <assert.h>

Logger& Logger::Get() {
	static Logger logger;
	return logger;
}

void Logger::Shutdown() {
	Get()._file.close();
}

const char* Logger::LogLevelToString(LogLevel level) {
	switch (level) {
		case LogLevel::Verbose: return "Verbose";
		case LogLevel::Debug: return "Debug";
		case LogLevel::Info: return "Info";
		case LogLevel::Warning: return "Warning";
		case LogLevel::Error: return "Error";
		case LogLevel::Fatal: return "Fatal";
	}
	assert(false);
	return "Unknown";
}

void Logger::DoLog(LogLevel level, const char* text) {
	// build message with time, level, pid, tid, text
	std::stringstream message;
	char time[48];
	const auto now = ::time(nullptr);
#ifdef _WINDOWS
	tm lt;
	localtime_s(&lt, &now);
	auto plt = &lt;
#else
	auto plt = localtime(&now);
#endif
	strftime(time, sizeof(time), "%D %T", plt);

	message
		<< "[" << time << "]"
		<< " [" << LogLevelToString(level) << "]"
		<< " [" << OS::GetPid() << "," << OS::GetTid() << "] "
		<< text	<< std::endl;

	AutoLock locker(_lock);
	_file << message.str();
}

Logger::Logger() {
	auto logDir = OS::ReadEnvironmentVariable("DotNext_LogDir");
	if (logDir.empty())
		logDir = OS::GetCurrentDir();
	else {
	}
}
