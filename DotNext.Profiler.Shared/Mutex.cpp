#include "Mutex.h"

#ifndef _WINDOWS

#include <mutex>

struct Mutex::Impl {
	void lock() {
		_mutex.lock();
	}

	void unlock() {
		_mutex.unlock();
	}

private:
	std::mutex _mutex;
};

Mutex::Mutex() : _impl(new Impl) {}
Mutex::~Mutex() = default;

void Mutex::lock() {
	_impl->lock();
}

void Mutex::unlock() {
	_impl->unlock();
}

#endif
