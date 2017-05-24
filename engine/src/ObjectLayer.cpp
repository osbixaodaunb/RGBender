#include "ObjectLayer.h"
#include "GameObject.h"

void ObjectLayer::update(){
	for(auto gameObject : m_gameObjects){
		gameObject->update();
	}
}

void ObjectLayer::render(){
	for(auto gameObject : m_gameObjects){
		gameObject->draw();
	}
}
