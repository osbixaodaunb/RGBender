#include "SDLGameObject.h"
#include "Game.h"

using namespace engine;

SDLGameObject::SDLGameObject() : GameObject() {
}

void SDLGameObject::load(const LoaderParams *pParams){
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0,0);
	m_acceleration = Vector2D(0,0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames = pParams->getNumFrames();
	m_angle = pParams->getAngle();
	m_collider = pParams->getCollider();
}

void SDLGameObject::draw(){
	int x = (int) m_position.getX();
	int y = (int) m_position.getY();

	SDL_RendererFlip flip = m_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), flip, m_angle);
	
}

void SDLGameObject::update(){
	//m_position += m_velocity;
	//m_velocity += m_acceleration;
}

void SDLGameObject::clean(){

}
