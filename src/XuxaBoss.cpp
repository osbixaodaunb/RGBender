#include "XuxaBoss.h"
#include "Log.h"

using namespace engine;

XuxaBoss::XuxaBoss() : Enemy(){
	m_states.push_back(&XuxaBoss::quarterLife);
	m_states.push_back(&XuxaBoss::halfLife);
	m_states.push_back(&XuxaBoss::fullLife);
	m_states.back()(); //Deve iniciar/executar o primeiro estado "FULL LIFE"
}

void XuxaBoss::fullLife(){
	//TODO
	INFO("Xuxa está com HP cheio!")
}

void XuxaBoss::halfLife(){
	//TODO
	INFO("Xuxa perdeu metade do HP!")
}

void XuxaBoss::quarterLife(){
	//TODO
	INFO("Xuxa perdeu 3/4 do HP!")
}

void XuxaBoss::load(const LoaderParams* pParams){
	Enemy::load(pParams);
	INFO("Created Xuxa boss");
}

void XuxaBoss::draw(){
	Enemy::draw();
}

void XuxaBoss::update(){

	Enemy::update();
}

void XuxaBoss::clean(){
	Enemy::clean();
}