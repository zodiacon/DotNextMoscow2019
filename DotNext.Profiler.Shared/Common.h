#pragma once

#include <stdint.h>
#include <unknwn.h>

#ifdef _WINDOWS
#include <atlbase.h>
#else
typedef int32_t HRESULT;
struct CAtlException {
	HRESULT HResult;
	CAtlException(HRESULT hr) : HResult(hr) {}
};
#define AtlThrow(hr) throw CAtlException(hr)
//#include <atl.h>
#endif
