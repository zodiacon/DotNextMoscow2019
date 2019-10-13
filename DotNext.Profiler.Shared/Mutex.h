#pragma once

#ifdef _WINDOWS

#include <mutex>
using Mutex = std::mutex;

#else

#include <memory>

class Mutex {
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
#endif


