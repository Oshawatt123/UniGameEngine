#include "Bitmap.h"
#include <string>
#include<iostream>
#include "SDL.h"
#include "SDL_render.h"

Bitmap::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	// grab the rednerer
	m_pRenderer = renderer;

	//create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP("dirtyfilename.png");
	if (!m_pbitmapSurface) {
		// bitmap not loaded. Do the dirty shame
		std::cout << "SURFACE for bitmap '%s' " << fileName << "not loaded! \n";
		std::cout << SDL_GetError() << "\n";
	}
	else {
		// remove transparent pixels
		// assume transparency colour is magenta (255,0,255)
		if (useTransparency) {
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		//create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture) {
			// texture not loaded. Do the dirty shame
			std::cout << "TEXTURE for bitmap '%s' " << fileName << "not loaded! \n";
			std::cout << SDL_GetError() << "\n";
		}
	}

	// store position values
	m_x = xpos;
	m_y = ypos;
}

Bitmap::~Bitmap()
{
}

void Bitmap::draw()
{
}
