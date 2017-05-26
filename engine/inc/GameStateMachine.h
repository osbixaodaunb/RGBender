#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "GameState.h"

#include <vector>

namespace engine{

	class GameStateMachine{
	public:
		void pushState(GameState* pState);
		void changeState(GameState* pState);
		void popState();
		void update();
		void render();

		GameState* currentState(){
			return m_gameStates.back();
		}

	private:
		std::vector<GameState*> m_gameStates;
	};

}
#endif
