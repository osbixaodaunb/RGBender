#include "PlayState.h"
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "PauseState.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "SDLGameObject.h"
#include "StateParser.h"
#include "Level.h"
#include "LevelParser.h"
#include "Log.h"
#include <string>
#include <iostream>

using namespace std;

using namespace engine;

const string PlayState::s_playID = "PLAY";

void PlayState::update(){
	//if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)){
	//	Game::Instance().getStateMachine()->pushState(new PauseState());
	//}

	if(InputHandler::Instance().isKeyDown("p"))
		Game::Instance().getStateMachine()->pushState(new PauseState());

	GameState::update();
	if(pLevel != NULL)
		pLevel->update();

	if(InputHandler::Instance().isKeyDown("q")){
		Game::Instance().getStateMachine()->pushState(new GameOverState());
	}
	m_playerLife = m_player->getLife();
	
	//if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
	//	Game::Instance().getStateMachine()->pushState(new GameOverState());
	//}
}

void PlayState::render(){

	if(pLevel != NULL){
		pLevel->render();
	}
	TextureManager::Instance().draw("health", 0, 0, m_playerLife, 32, Game::Instance().getRenderer());
	TextureManager::Instance().draw("instance", 100, 600, 100, 100, Game::Instance().getRenderer());
	GameState::render();
}


bool PlayState::onEnter(){	
	//StateParser stateParser;
	//stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);
	Game::Instance().setScore(0);
	TextureManager::Instance().loadText(to_string(Game::Instance().getScore()), "assets/fonts/Lato-Regular.ttf", "score", {255,255,255}, 50, Game::Instance().getRenderer());
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/mapadoidao.tmx");
	m_player = pLevel->getPlayer();
	INFO("Entering PlayState");
	return true;
}

bool PlayState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("helicopter");
	TextureManager::Instance().clearFromTextureMap("RAG");
	INFO("Exiting PlayState");
	return true;
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2){
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if(bottomA <= topB) return false;
	if(topA >= bottomB) return false;
	if(rightA <= leftB) return false;
	if(leftA >= rightB) return false;

	return true;
}
