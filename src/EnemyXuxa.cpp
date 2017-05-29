#include "EnemyXuxa.h"
#include "Log.h"
#include "InputHandler.h"
EnemyXuxa::EnemyXuxa() : Enemy(){
	m_states.push_back(&EnemyXuxa::quarterLife);
	m_states.push_back(&EnemyXuxa::halfLife);
	m_states.push_back(&EnemyXuxa::fullLife);
	m_states.back()(); //Deve iniciar/executar o primeiro estado "FULL LIFE"
}

void EnemyXuxa::fullLife(){
	//TODO
	INFO("Xuxa está com HP cheio!")
}

void EnemyXuxa::halfLife(){
	//TODO
	INFO("Xuxa perdeu metade do HP!")
}

void EnemyXuxa::quarterLife(){
	//TODO
	INFO("Xuxa perdeu 3/4 do HP!")
}
void EnemyXuxa::draw(){
	Enemy::draw();
}
void EnemyXuxa::update(){
	Enemy::update();
}
void EnemyXuxa::clean(){
	Enemy::clean();
}
