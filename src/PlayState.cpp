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

#include <string>
#include <iostream>

using namespace std;

const string PlayState::s_playID = "PLAY";

Level *pLevel = NULL;

void PlayState::update(){
	//if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)){
	//	Game::Instance().getStateMachine()->pushState(new PauseState());
	//}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_P))
		Game::Instance().getStateMachine()->pushState(new PauseState());

	GameState::update();
	if(pLevel != NULL)
		pLevel->update();

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_Q)){
		Game::Instance().getStateMachine()->pushState(new GameOverState());
	}

	//if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
	//	Game::Instance().getStateMachine()->pushState(new GameOverState());
	//}
}

void PlayState::render(){

	if(pLevel != NULL){
		pLevel->render();
	}


	GameState::render();
}

bool PlayState::onEnter(){	
	//StateParser stateParser;
	//stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/mapadoidao.tmx");

	cout <<	"Entering PlayState" << endl;
	return true;
}

bool PlayState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("helicopter");

	cout << "Exiting PlayState" << endl;	
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
