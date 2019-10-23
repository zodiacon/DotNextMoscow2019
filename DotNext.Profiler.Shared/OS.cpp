#include "OS.h"

#ifdef _WINDOWS
#include <Windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#endif

std::string OS::ReadEnvironmentVariable(const char* name) {
#ifdef _WINDOWS
	char value[1024];
	::GetEnvironmentVariableA(name, value, sizeof(value));
	return value;
#else
	return ::getenv(name);
#endif
}

int OS::GetPid() {
#ifdef _WINDOWS
	return ::GetCurrentProcessId();
#else
	return getpid();
#endif
}

int OS::GetTid() {
#ifdef _WINDOWS
	return ::GetCurrentThreadId();
#else
	return pthread_self();
#endif
}

std::string OS::GetCurrentDir() {
	char buffer[512] = { 0 };
#ifdef _WINDOWS
	::GetCurrentDirectoryA(sizeof(buffer), buffer);
#else
	getcwd(buffer, sizeof(buffer));
#endif
	return buffer;
}
