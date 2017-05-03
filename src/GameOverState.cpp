#include "GameOverState.h"
#include "GameState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"


#include <iostream>

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update(){
	GameState::update();
}

void GameOverState::render(){
	GameState::render();
}

void GameOverState::s_gameOverToMain(){
	Game::Instance().getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay(){
	Game::Instance().getStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter(){
	StateParser stateParser;
	stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);
	
	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	std::cout << "Entering GameOverState\n";
	return true;
}

bool GameOverState::onExit(){
	GameState::onExit();

	std::cout << "Exiting GameOverState\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks){
	// go through game objects
	for(auto gameObject : m_gameObjects){
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(gameObject)){
			MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}
