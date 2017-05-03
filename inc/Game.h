#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "GameObject.h"
#include "GameStateMachine.h"

#include <SDL2/SDL.h>
#include <vector>

class Game{
public:
	
	static Game& Instance(){
		static Game game;

		return game;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	bool init(const char*, int, int, int, int, bool);

	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();
	void quit();

	SDL_Renderer* getRenderer(){
		return m_pRenderer;
	}

	bool running() { return m_bRunning; }
	GameStateMachine* getStateMachine(){
		return m_pGameStateMachine;
	}

	int getGameWidth() const{
		return m_gameWidth;
	}

	int getGameHeight() const {
		return m_gameHeight;
	}

private:
	Game() {}

	int m_gameWidth;
	int m_gameHeight;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;

	std::vector<GameObject*> m_gameObjects;

	int m_currentFrame;
	bool m_bRunning;

	GameStateMachine *m_pGameStateMachine;
};

#endif
