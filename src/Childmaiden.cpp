#include "Childmaiden.h"
#include <math.h>
#include "Vector2D.h"
#include "Game.h"
#include "SDLGameObject.h"
#include <iostream>
#include "Timer.h"
using namespace std;
using namespace engine;

Childmaiden::Childmaiden(){
	isVisible = true;
	sinalx = 1;
	sinaly = 1;
	engine::Game::Instance().getStateMachine()->currentState()->addShieldObject(this);
	m_velocity = engine::Vector2D(0, 0);
	originTime = engine::Timer::Instance().step();
}

engine::Vector2D rotateVec(engine::Vector2D vec, double ang){
	engine::Vector2D result;
	
	result.setX(vec.getX() * cos(ang) - vec.getY() * sin(ang));
	result.setY(vec.getX() * sin(ang) + vec.getY() * cos(ang));

	return result;
}

void Childmaiden::update(){
	m_currentFrame = int(((SDL_GetTicks() / 300) % m_numFrames));
	m_position = Vector2D(685, 187) + rotateVec(startPoint,
				(engine::Timer::Instance().step() - originTime) / 1000.0);
	
}

void Childmaiden::load(const engine::LoaderParams *pParams){
	SDLGameObject::load(pParams);
	
	std::vector<SDLGameObject*> v = engine::Game::Instance().getStateMachine()->currentState()->getShieldObjects();
	for(int i = 0; i < v.size(); i++){
		if(this == dynamic_cast<Childmaiden*>(v[i])){
			Vector2D vec(0,130);
			m_position = Vector2D(685,187) + rotateVec(vec, 72 * i);
			cout << v.size() << endl;
		}
	}

	startPoint = m_position - Vector2D(685, 187);
}

void Childmaiden::draw(){
	if(isVisible)
		SDLGameObject::draw();
}

void Childmaiden::clean(){
	SDLGameObject::clean();
}