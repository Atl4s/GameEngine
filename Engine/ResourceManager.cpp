#include "ResourceManager.h"

ResourceManager* ResourceManager::s_pInstance = 0;

bool ResourceManager::load(std::string fileName,
	std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0){	return false; }
	SDL_Texture* pTexture =
		SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

void ResourceManager::draw(std::string id, int x, int y,
	int width, int height, SDL_Renderer* pRenderer,
	SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}

void ResourceManager::drawFrame(std::string id, int x, int y, 
	int width, int height, int currentRow, int currentFrame, 
	SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}

void ResourceManager::drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
	SDL_RenderDrawPoint(pRenderer, x, y);
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void ResourceManager::drawVector(glm::vec2 position, glm::vec2 vector, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
	SDL_RenderDrawLine(pRenderer, position.x, position.y, position.x + vector.x, position.y + vector.y);
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void ResourceManager::drawRect(glm::vec2 position, glm::vec2 vector, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = vector.x;
	rect.h = vector.y;
	SDL_RenderFillRect(pRenderer, &rect);
	SDL_RenderDrawRect(pRenderer, &rect);
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}