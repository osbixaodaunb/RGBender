#include "PauseState.h"
#include "Game.h"
#include "GameState.h"
#include "TextureManager.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

#include <iostream>
#include <string>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
	Game::Instance().getStateMachine()->popState();
	Game::Instance().getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay(){
	Game::Instance().getStateMachine()->popState();
}

void PauseState::update(){
	GameState::update();
}

void PauseState::render(){
	GameState::render();
}

bool PauseState::onEnter(){
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	std::cout << "Entering PauseState" << std::endl;

	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
	for(auto gameObject : m_gameObjects){
		if(dynamic_cast<MenuButton*>(gameObject)){
			MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

bool PauseState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("resumeButton");
	TextureManager::Instance().clearFromTextureMap("menuButton");

	InputHandler::Instance().reset();

	std::cout << "Exiting PauseState" << std::endl;
	return true;

}
