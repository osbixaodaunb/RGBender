#include <Timer.h>
#include <iostream>

using namespace engine;

void Timer::start(){
	m_time = SDL_GetTicks();
}

Uint32 Timer::step(){
	//std::cout << "TICKS: " << SDL_GetTicks() << std::endl;
	//std::cout << "STEP: " << (SDL_GetTicks() - m_time) << std::endl;
	return SDL_GetTicks() - m_time;
}

void Timer::stop(){
	m_time = 0;
}
