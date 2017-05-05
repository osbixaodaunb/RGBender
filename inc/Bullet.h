#ifndef BULLET_H
#define BULLET_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class Bullet : public SDLGameObject{
public:
	Bullet();

	void load(const LoaderParams* pParams, Vector2D p_velocity);
	void load(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();

private:

	int m_moveSpeed = 1;
	int m_moveCounter;

	int m_dyingTime;
	int m_dyingCounter;
};


#endif
