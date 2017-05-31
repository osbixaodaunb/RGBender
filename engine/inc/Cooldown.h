#ifndef COOLDOWN_H
#define COOLDOWN_H

#include <functional>
#include <iostream>

#include "Timer.h"

namespace engine{
	template<typename T>
	class Cooldown{
	public:
		Cooldown(double seconds, std::function<void(T)> callback, T value){
			m_seconds = seconds + Timer::Instance().step();
			m_callback = callback;

			m_value = value;
		}

		bool update(){
			if(Timer::Instance().step() > m_seconds){
				m_callback(m_value);
				return true;
			}

			return false;
		}

	private:
		double m_seconds;

		T m_value;
		std::function<void(T)> m_callback;
	};
}
#endif
