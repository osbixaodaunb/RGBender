#ifndef __PLAYERSHIELD__
#define __PLAYERSHIELD__

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Player.h"
#include "Enemy.h"
#inc
class PlayerShield : public engine::SDLGameObject{
public:
	PlayerShield();
	~PlayerShield();

	void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	void checkCollision();
	// void setPlayer(Player* p_player){
	// 	m_player = p_player;
	// }

private:
	
	Enemy* m_boss = NULL;
	bool m_active;
	int numberHits;
};

class PlayerShieldCreator{
	PlayerShield* create(){
		return new PlayerShield();
	}
};
#endif