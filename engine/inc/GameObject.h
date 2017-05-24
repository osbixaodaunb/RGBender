#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoaderParams.h"

#include <SDL2/SDL.h>
#include <string>

class GameObject{
public:
	virtual	void draw()=0;
	virtual void update()=0;
	virtual void clean()=0;

	virtual void load(const LoaderParams* pParams) = 0;

	virtual std::string getTextureID() = 0;
protected:
	GameObject() {}
	virtual ~GameObject() {}
};

#endif
