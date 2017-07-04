#ifndef CHILDMAIDEN_H
#define CHILDMAIDEN_H

#include "SDLGameObject.h"
#include "BaseCreator.h"

class Childmaiden : public engine::SDLGameObject{

public:
	Childmaiden();
	virtual void load(const engine::LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void setVisibility(bool visibility){
		isVisible = visibility;
	}

	bool getVisibility(){
		return isVisible;
	}

private:
	bool isVisible;
	int phi;
	int sinalx, sinaly;
};

class ChildmaidenCreator : public engine::BaseCreator{
public:
	engine::GameObject* createGameObject() const{
		return new Childmaiden();
	}

};

#endif