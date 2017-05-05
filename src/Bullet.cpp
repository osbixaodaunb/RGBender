#include "Bullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"

#include <iostream>

Bullet::Bullet() : SDLGameObject(){

}

void Bullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

void Bullet::load(const LoaderParams* pParams, Vector2D pVelocity){

	SDLGameObject::load(pParams);
	m_velocity = pVelocity.norm() * m_moveSpeed;
}

void Bullet::draw(){
	SDLGameObject::draw();
}

void Bullet::update(){
	m_position += m_velocity;
}

void Bullet::clean(){
	SDLGameObject::clean();
}

