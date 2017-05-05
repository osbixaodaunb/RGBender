#include <Timer.h>

void Timer::start(){
	m_time = SDL_GetTicks();
}

void Timer::reset(){
	Timer::setTime(0);
}