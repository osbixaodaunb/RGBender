#include "Level.h"

#include <vector>

using namespace engine;

void Level::render(){
	for(auto layer : m_layers){
		layer->render();
	}
}

void Level::update(){
	for(auto layer : m_layers){
		layer->update();
	}
}
