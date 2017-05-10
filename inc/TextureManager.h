#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <map>

class TextureManager{
public:
	bool load(std::string, std::string, SDL_Renderer*);	
	void draw(std::string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0);
	void drawTile(std::string, int, int, int, int, int, int, int, int, SDL_Renderer *pRenderer);

	static TextureManager& Instance(){
		static TextureManager instance;
		
		return instance;
	}
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	void clearFromTextureMap(std::string id){
		m_textureMap.erase(id);
	}

	void changeColorPixels(uint8_t* pixelColors){
		SDL_Texture* pTexture = m_textureMap["bullet"];
		SDL_SetTextureColorMod( pTexture, pixelColors[0],pixelColors[1], pixelColors[2] );
	}

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	TextureManager() { }
};


typedef TextureManager TheTextureManager;

#endif
