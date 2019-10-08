#include "Bitmap.h"

#include "SDL.h"
#include "SDL_render.h"

Bitmap::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	// grab the rednerer
	m_pRenderer = renderer;

	//create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface) {
		// bitmap not loaded. Do the dirty shame
		std::printf("SURFACE for bitmap '%s' not loaded! \n", fileName.c_str());
		std::printf("%s\n", SDL_GetError());
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
			std::printf("TEXTURE for bitmap '%s' not loaded! \n", fileName.c_str());
			std::printf("%s\n", SDL_GetError());
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
