#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	m_pRenderer = renderer;
}

BitMapPack ResourceManager::Load(std::string filePath, bool transparency)
{

	BitMapPack returnPack;
	returnPack.texture = nullptr;
	returnPack.width = NULL;
	returnPack.height = NULL;

	// create bitmap surface
	m_pBitMapTempSurface = SDL_LoadBMP(filePath.c_str());
	// check bitmap surface was created successfully
	if (!m_pBitMapTempSurface) {
		// bitmap not loaded. Do the dirty shame
		std::cout << "SURFACE for bitmap " << filePath << " not loaded! \n";
		std::cout << SDL_GetError() << "\n";
	}
	else
	{
		// add to the BitMapPack
		returnPack.width = m_pBitMapTempSurface->w;
		returnPack.height = m_pBitMapTempSurface->h;

		// remove transparent pixels
		if (transparency)
		{
			// assume transparency colour is magenta (255,0,255)
			Uint32 colourKey = SDL_MapRGB(m_pBitMapTempSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pBitMapTempSurface, SDL_TRUE, colourKey);
		}
	}

	// create bitmap texture
	m_pBitMapTempTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pBitMapTempSurface);
	if (!m_pBitMapTempTexture)
	{
		// texture not loaded. Do the dirty shame
		std::cout << "TEXTURE for bitmap '%s' " << filePath << "not loaded! \n";
		std::cout << SDL_GetError() << "\n";
	}
	else
	{
		// add to the BitMapPack
		returnPack.texture = m_pBitMapTempTexture;
	}

	if (m_pBitMapTempSurface)
	{
		SDL_FreeSurface(m_pBitMapTempSurface);
	}

	return returnPack;
}
