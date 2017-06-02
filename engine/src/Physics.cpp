#include "Physics.h"
#include "SDLGameObject.h"

#include <iostream>

using namespace engine;

using namespace std;

bool Physics::checkCollision(SDLGameObject* p1, SDLGameObject* p2){
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX() + (p1->getWidth()-p1->getCollider().getWidth())/2;
	rightA = p1->getPosition().getX() + (p1->getWidth() + p1->getCollider().getWidth())/2;
	topA = p1->getPosition().getY() + (p1->getHeight() - p1->getCollider().getHeight())/2;
	bottomA = p1->getPosition().getY() + (p1->getHeight() + p1->getCollider().getHeight())/2;

	leftB = p2->getPosition().getX() + (p2->getWidth()-p2->getCollider().getWidth())/2;
	rightB = p2->getPosition().getX() + (p2->getWidth() + p2->getCollider().getWidth())/2;
	topB = p2->getPosition().getY() + (p2->getHeight() - p2->getCollider().getHeight())/2;
	bottomB = p2->getPosition().getY() + (p2->getHeight() + p2->getCollider().getHeight())/2;


	if(bottomA <= topB) return false;
	if(topA >= bottomB) return false;
	if(rightA <= leftB) return false;
	if(leftA >= rightB) return false;

	return true;
}

