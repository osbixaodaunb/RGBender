#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include "GameObject.h"

#include <string>
#include <map>

class BaseCreator{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator(){}
};

#endif
