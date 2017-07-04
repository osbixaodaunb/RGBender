#ifndef __PLAYERSHIELD__
#define __PLAYERSHIELD__

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Player.h"

class PlayerShield : public engine::SDLGameObject{
public:
	PlayerShield(Player* p_player){
		setPlayer(p_player);
	}
	~PlayerShield();

	void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	void checkCollision();

private:
	void setPlayer(Player* p_player){
		m_player = p_player;
	}
	Player* m_player;
};

class PlayerShieldCreator{
	PlayerShield* create(Player *p_player){
		return new PlayerShield(p_player);
	}
};
#endif