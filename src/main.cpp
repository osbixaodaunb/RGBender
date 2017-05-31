#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

using namespace engine;

int main(int argc, char* argv[]){

	Uint32 frameStart, frameTime;

	const int center = Game::Instance().getCenterScreen();
	Game::Instance().init("Chapter 1", center, center,
						  1366, 768, false);

	while(Game::Instance().running()){
		frameStart = SDL_GetTicks();

		Game::Instance().handleEvents();
		Game::Instance().update();
		Game::Instance().render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameTime < DELAY_TIME){
			SDL_Delay((int) (DELAY_TIME - frameTime));
		}
	}

	Game::Instance().clean();

	return 0;
}
