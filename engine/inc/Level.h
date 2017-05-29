#ifndef LEVEL_H
#define LEVEL_H

#include "Layer.h"
//migue
#include "XuxaBoss.h"
#include "Log.h"

#include <string>
#include <vector>

namespace engine{

	struct Tileset{
		int firstGridID;
		int tileWidth;
		int tileHeight;
		int spacing;
		int margin;
		int width;
		int height;
		int numColumns;
		std::string name;
	};

	class Level{
	public:
		~Level(){}

		void update();
		void render();

		std::vector<Tileset>* getTilesets(){
			return &m_tilesets;
		}

		std::vector<Layer*>* getLayers(){
			return &m_layers;
		}

		void setXuxa(XuxaBoss *p_xuxa){
			m_xuxa = p_xuxa;
		}

		XuxaBoss* getXuxa(){
			return m_xuxa;
		}

	private:
		std::vector<Tileset> m_tilesets;
		std::vector<Layer*> m_layers;

		XuxaBoss *m_xuxa = NULL;

		friend class LevelParser;
		Level(){}
	};
}

#endif
