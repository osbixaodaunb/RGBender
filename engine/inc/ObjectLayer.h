#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "Layer.h"
#include "GameObject.h"

#include <vector>

namespace engine{

	class ObjectLayer : public Layer{
	public:
		virtual void update();
		virtual void render();

		std::vector<GameObject*> *getGameObjects(){
			return &m_gameObjects;
		}

	private:
		std::vector<GameObject*> m_gameObjects;
	};
}
#endif
