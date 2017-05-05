#include <Timer.h>
#include <iostream>

void Timer::start(){
	m_time = SDL_GetTicks();
	std::cout << m_time << std::endl;
}

Uint32 Timer::step(){
	return SDL_GetTicks() - m_time;
}

void Timer::stop(){
	m_time = 0;
}