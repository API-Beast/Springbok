// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "PreciseClock.h"
#include <Springbok/Config.h>

#ifdef SPRINGBOK_WINDOWS
  #include <windows.h>
#endif
#ifdef SPRINGBOK_MAC
  #include <mach/mach.h>
  #include <mach/mach_time.h>
#endif
#ifdef SPRINGBOK_LINUX
  #include <time.h>
#endif

struct PreciseClockData
{
#ifdef SPRINGBOK_WINDOWS
	LARGE_INTEGER StartTime;
#endif
#ifdef SPRINGBOK_MAC
	uint64_t StartTime;
#endif
#ifdef SPRINGBOK_LINUX
	timespec StartTime;
#endif
};

namespace
{
#ifdef SPRINGBOK_WINDOWS
double gConversion = 0.0;
#endif

#ifdef SPRINGBOK_MAC
double gConversion = 0.0;
#endif

#ifdef SPRINGBOK_LINUX
double gPrecision = 0.0;
#endif
}

PreciseClock::PreciseClock()
{
	d = new PreciseClockData;
#ifdef SPRINGBOK_WINDOWS 
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	gConversion = 1.0 / double(freq.QuadPart);
#endif
#ifdef SPRINGBOK_MAC
	if(gConversion == 0.)
	{
		mach_timebase_info_data_t info;
		mach_timebase_info(&info);
		gConversion = 1e-9 * (double) info.numer / (double) info.denom;
	}
#endif
#ifdef SPRINGBOK_LINUX
	if(gPrecision == 0.)
	{
		timespec res;
		clock_getres(CLOCK_MONOTONIC, &res);
		gPrecision = res.tv_sec + res.tv_nsec * 0.000001;
	}
#endif
	start();
}

PreciseClock::~PreciseClock()
{
	delete d;
}

void PreciseClock::start()
{
#ifdef SPRINGBOK_WINDOWS
	QueryPerformanceCounter(&(d->StartTime));
#endif
#ifdef SPRINGBOK_MAC
	StartTime = mach_absolute_time();
#endif
#ifdef SPRINGBOK_LINUX
	clock_gettime(CLOCK_MONOTONIC, &(d->StartTime));
#endif
}

double PreciseClock::elapsed()
{
#ifdef SPRINGBOK_WINDOWS                      
	LARGE_INTEGER curTime;
	QueryPerformanceCounter(&curTime);
	return (curTime.QuadPart - d->StartTime.QuadPart) * gConversion;
#endif

#ifdef SPRINGBOK_MAC
	return (mach_absolute_time() - StartTime) * gConversion;
#endif

#ifdef SPRINGBOK_LINUX
	timespec curTime;
	clock_gettime(CLOCK_MONOTONIC, &curTime);
	return double(curTime.tv_sec - d->StartTime.tv_sec) + double(curTime.tv_nsec - d->StartTime.tv_nsec) * 1e-9;
#endif
}

bool PreciseClock::isMonotonic()
{
	return true;
}

double PreciseClock::getResolution()
{
#ifdef SPRINGBOK_WINDOWS
	return gConversion;
#endif
#ifdef SPRINGBOK_MAC
	return gConversion;
#endif
#ifdef SPRINGBOK_LINUX
	return gPrecision;
#endif
}

