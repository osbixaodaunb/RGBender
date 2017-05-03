#include "TileLayer.h"
#include "Level.h"
#include "Game.h"

#include <iostream>
#include <vector>


TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0){

	// Se algum dia a parada der ruim, e tu não saber oq ta dando, olha nessa linha daqui
	m_numColumns = (Game::Instance().getGameWidth()/ m_tileSize + m_tileSize);
	m_numRows = (Game::Instance().getGameHeight() / m_tileSize);
}

Tileset TileLayer::getTilesetByID(int tileID){
	return m_tilesets.front();
}

void TileLayer::update(){
	m_position += m_velocity;
	m_velocity.setX(1);
}

void TileLayer::render(){
	
	int x, x2, y2 = 0;

	x = m_position.getX() / m_tileSize;

	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;
	
	for(int i = 0; i < m_numRows; i++){
		for(int j = 0; j < m_numColumns; j++){
			int id = m_tileIDs[i][j + x];

			if(id == 0){
				continue;
			}
			Tileset tileset = getTilesetByID(id);
			id--;

			TextureManager::Instance().drawTile(tileset.name, 2, 2, (j * m_tileSize) - x2, 
					(i * m_tileSize) - y2, m_tileSize, m_tileSize, 
					(id - (tileset.firstGridID - 1)) / tileset.numColumns, 
					(id - (tileset.firstGridID - 1)) %	tileset.numColumns, Game::Instance().getRenderer());
		}
	}
}
