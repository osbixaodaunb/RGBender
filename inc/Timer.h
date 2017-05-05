#ifndef __TIMER__
#define __TIMER__

#include <SDL2/SDL.h>

class Timer{

public:
	Timer() {}
	void start();
	void reset();
	Uint32 getTime() { return m_time;}
	void setTime(Uint32 time) { m_time = time;}

private:
	Uint32 m_time;
};

#endif