#ifndef PHYSICS_H
#define PHYSICS_H

#include "SDLGameObject.h"
namespace engine{
	class Physics{
	public:
		static Physics& Instance(){
			static Physics instance;

			return instance;
		}

		Physics(Physics const&) = delete;
		void operator=(Physics const&) = delete;

		bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	private:
		Physics(){}


	};
}
#endif
