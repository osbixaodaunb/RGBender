#include "Level.h"

#include <vector>

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
