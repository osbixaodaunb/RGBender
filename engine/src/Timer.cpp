#include <Timer.h>
#include <iostream>

using namespace engine;

void Timer::start(){
	m_time = SDL_GetTicks();
}

Uint32 Timer::step(){
	return SDL_GetTicks() - m_time;
}

void Timer::stop(){
	m_time = 0;
}
