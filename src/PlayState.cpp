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
#include "AudioManager.h"
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

	
	m_playerLife = m_player->getLife();
	
	//if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
	//	Game::Instance().getStateMachine()->pushState(new GameOverState());
	//}
}

void PlayState::render(){

	if(pLevel != NULL){
		pLevel->render();
	}

	TextureManager::Instance().draw("emptyhealthboss", 500, m_boss->getPosition().getY()+40, 424, 60, Game::Instance().getRenderer());
	TextureManager::Instance().draw("healthboss", 500+11, m_boss->getPosition().getY()+57, m_boss->getHealth()-20,28, Game::Instance().getRenderer());
	TextureManager::Instance().draw("madreXuxa", 630, m_boss->getPosition().getY(), 180, 60, Game::Instance().getRenderer());
	GameState::render();
}


bool PlayState::onEnter(){	
	//StateParser stateParser;
	//stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);
	Game::Instance().setScore(0);
	TextureManager::Instance().loadText(to_string(Game::Instance().getScore()), "assets/fonts/Lato-Regular.ttf", "score", {255,255,255}, 50, Game::Instance().getRenderer());
	AudioManager::Instance().playMusic("assets/sounds/xuxabeat.mp3");
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/mapadoidao.tmx");
	m_player = pLevel->getPlayer();
	m_boss = pLevel->getXuxa();
	INFO("Entering PlayState");
	return true;
}

bool PlayState::onExit(){
	GameState::onExit();
	AudioManager::Instance().stop();
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
