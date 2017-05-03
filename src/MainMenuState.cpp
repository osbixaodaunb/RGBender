#include "MainMenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PlayState.h"
#include "GameState.h"
#include "Player.h"
#include "StateParser.h"

#include <vector>
#include <iostream>

using namespace std;

const string MainMenuState::s_menuID = "MENU";

void MainMenuState::update(){
	GameState::update();
}

void MainMenuState::render(){
	GameState::render();
}

bool MainMenuState::onEnter(){
	// parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0); // pushback 0 callbackID starts with 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	cout << "Entering MainMenuState" << endl;
	return true;
}

void MainMenuState::setCallbacks(const vector<Callback> &callbacks){
	// go through game objects
	for(auto gameObject : m_gameObjects){
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(gameObject)){
			MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

bool MainMenuState::onExit(){
	GameState::onExit();

	cout << "Exiting MainMenuState" << endl;
	
	return true;
}

void MainMenuState::s_menuToPlay(){
	Game::Instance().getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu(){
	Game::Instance().quit();
}
