#include "SDLGameObject.h"
#include "Game.h"

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
}

void SDLGameObject::draw(){
	int x = (int) m_position.getX();
	int y = (int) m_position.getY();

	if(m_velocity.getX() > 0){
		TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), SDL_FLIP_HORIZONTAL);
	} else {
		TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer());
	}
}

void SDLGameObject::update(){
	m_position += m_velocity;
	m_velocity += m_acceleration;
}

void SDLGameObject::clean(){

}
