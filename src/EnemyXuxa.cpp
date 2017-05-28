#include "EnemyXuxa.h"

EnemyXuxa::EnemyXuxa() : Enemy(){

}

EnemyXuxa::fullLife(){
	//TODO
	INFO("Xuxa está com HP cheio!")
}

EnemyXuxa::halfLife(){
	//TODO
	INFO("Xuxa perdeu metade do HP!")
}

EnemyXuxa::quarterLife(){
	//TODO
	INFO("Xuxa perdeu 75%% do HP!")
}

EnemyXuxa::updateHealth(){
	if(InputHandler::Instance().isKeyDown("z")){
		m_actualHealth -= 20;
	}
}