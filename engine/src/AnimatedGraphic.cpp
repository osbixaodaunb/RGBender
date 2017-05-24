#include "AnimatedGraphic.h"
#include "SDLGameObject.h"

#include <iostream>

AnimatedGraphic::AnimatedGraphic() : SDLGameObject(){

}

void AnimatedGraphic::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::update(){
	SDLGameObject::update();
	m_currentFrame = int(((SDL_GetTicks() / (1000/m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::draw(){
	SDLGameObject::draw();
}

void AnimatedGraphic::clean(){
	SDLGameObject::update();
}
