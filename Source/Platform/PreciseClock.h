// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

class PreciseClockData;

/** A clock able to measure very short durations of time. (Precision should be higher than one millisecond.) */
class PreciseClock
{
public:
	PreciseClock();
	~PreciseClock();
	/** Starts the clock. */
	void start();
	/** Returns the number of seconds since the last call of start(). */
	double elapsed();
	/** Returns \c true if the used clock is monotonic. PreciseClock will use a monotonic clock if possible, however there might be none available. */
	bool isMonotonic();
	/** Returns the smallest amount of time the clock is able to measure. */
	double getResolution();
private:
	PreciseClockData* d;
};
