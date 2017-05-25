#ifndef LAYER_H
#define LAYER_H

namespace engine{

	class Layer{
	public:
		virtual void render() = 0;
		virtual void update() = 0;

	protected:
		virtual ~Layer() {}
	};
}
#endif
