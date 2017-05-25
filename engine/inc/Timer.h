#ifndef __TIMER__
#define __TIMER__

#include <SDL2/SDL.h>

namespace engine{

	class Timer{

	public:
		static Timer& Instance(){
			static Timer instance;

			return instance;
		}

		Timer(Timer const&) = delete;
		void operator=(Timer const&) = delete;

		void start();
		Uint32 step();
		void stop();

	private:
		Timer() {}
		Uint32 m_time;
		Uint32 m_lastTime;
	};

}
#endif