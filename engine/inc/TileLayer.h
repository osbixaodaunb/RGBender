#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Layer.h"
#include "Vector2D.h"
#include "Level.h"

#include <vector>

class TileLayer : public Layer{
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);

	virtual void update();
	virtual void render();

	Tileset getTilesetByID(int tileID);

	void setTileIDs(const std::vector<std::vector<int>>& data){
		m_tileIDs = data;
	}
	void setTileSize(int tileSize){
		m_tileSize = tileSize;
	}
private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset> &m_tilesets;
	std::vector<std::vector<int> > m_tileIDs;
};

#endif
