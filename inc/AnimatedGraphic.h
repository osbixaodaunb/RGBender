#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H

#include "SDLGameObject.h"
#include "BaseCreator.h"

class AnimatedGraphic : public SDLGameObject{
public:
	AnimatedGraphic();
	
	void load(const LoaderParams* pParams);

	void update();
	void draw();
	void clean();
private:
	int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator{
	GameObject* createGameObject() const{
		return new AnimatedGraphic();
	}
};


#endif
