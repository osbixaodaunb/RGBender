#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "XuxaBoss.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "GameObjectFactory.h"
#include "AnimatedGraphic.h"
#include "Timer.h"
#include "Log.h"
#include "Cooldown.h"
#include <iostream>
#include <vector>
#include "AudioManager.h"
#include <SDL2/SDL_image.h>

using namespace std;
using namespace engine;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	m_gameWidth = width;
	m_gameHeight = height;

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
		INFO("SDL init success");
			
		// init the window
		m_pWindow = SDL_CreateWindow(title, 
									 xpos, ypos, 
									 width, height, 
									 flags);
		
		if(m_pWindow != 0){
			// window init success
			INFO("Window creation success");
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0){
				// renderer init success
				INFO("Renderer creation success");
				SDL_SetRenderDrawColor(m_pRenderer,
										 255, 255, 255, 255);
			} else {
				// renderer init failed
				INFO("Renderer init failed");
					return false;
			}
		} else {
			// window init failed
			INFO("Window init failed");
			return false;
		}
	} else {
		// SDL init failed
		INFO("SDL init failed");
		return false;
	}

	if(!(AudioManager::Instance().init()))
		return false;

	INFO("AudioManager init success")

	InputHandler::Instance().initialiseJoysticks();
	INFO("Init success");

	Timer::Instance().start();
	
	// everything inited successfully, start the main loop
	m_bRunning = true;

	GameObjectFactory::Instance().registerType("MenuButton", new MenuButtonCreator());
	GameObjectFactory::Instance().registerType("XuxaBoss", new XuxaBossCreator());
	GameObjectFactory::Instance().registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance().registerType("AnimatedGraphic", new AnimatedGraphicCreator());


	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	return true;
}

void Game::draw(){
	for(GameObject* gameObject : m_gameObjects){
		gameObject->draw();
	}
}

void Game::render(){
	// clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();
	TextureManager::Instance().draw("score", 640, 0, 100, 100, Game::Instance().getRenderer());

	// draw to screen
	SDL_RenderPresent(m_pRenderer);
}

void Game::update(){
	m_pGameStateMachine->update();
	vector<Cooldown<int>*> doneCooldowns;

	for(auto cooldown : m_cooldowns){
		if(cooldown->update()){
			doneCooldowns.push_back(cooldown);
		}
	}
	if(!doneCooldowns.empty()){
		for(auto cooldown : doneCooldowns){
			m_cooldowns.erase(find(m_cooldowns.begin(), m_cooldowns.end(), cooldown));
		}
	}
}

void Game::handleEvents(){
	InputHandler::Instance().update();

	if(InputHandler::Instance().isKeyDown("left")){
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::clean(){
	INFO("Cleaning game");
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	InputHandler::Instance().clean();

	IMG_Quit();
	SDL_Quit();
}

void Game::quit(){
	m_bRunning = false;
}
