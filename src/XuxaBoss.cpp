#include "XuxaBoss.h"
#include "Log.h"

using namespace engine;

XuxaBoss::XuxaBoss() : Enemy(){
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