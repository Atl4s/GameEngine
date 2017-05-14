#pragma once
#include "libraries.h"
#include "glm/glm.hpp"
#include "TextureCache.h"

class ResourceManager
{
protected:
	static ResourceManager* s_pInstance;
	ResourceManager(){}
	virtual ~ResourceManager(){}
public:
	
	static ResourceManager* Instance()
	{
		if (s_pInstance == 0)  { s_pInstance = new ResourceManager();    return s_pInstance; }
		return s_pInstance;
	}

	static bool DeleteInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = 0;
			return true;
		}
		return false;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer);

	void drawVector(glm::vec2 vec1, glm::vec2 vec2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer);

	void drawRect(glm::vec2 position, glm::vec2 vector, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer);

	void clearFromTextureMap(std::string id)
	{ 
		SDL_DestroyTexture(m_textureMap.at(id));
		m_textureMap.erase(id); 
	}

	GLTexture getTexture(std::string textureCache)
	{
		return m_textureCache.getTexture(textureCache);
	}

private:
	std::map<std::string, SDL_Texture*> m_textureMap;

	TextureCache m_textureCache;
};