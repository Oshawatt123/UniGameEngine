#include "Bitmap.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_render.h"

Bitmap::Bitmap(SDL_Renderer* renderer, int xPos, int yPos, BitMapPack bmpPack)
{
	// grab the renderer
	m_pRenderer = renderer;

	// store position values
	m_x = xPos;
	m_y = yPos;

	// store loaded texture
	m_pbitmapTexture = bmpPack.texture;

	// store size values for bitmap
	m_w = bmpPack.width;
	m_h = bmpPack.height;
}

Bitmap::~Bitmap()
{
	if (m_pbitmapTexture) SDL_DestroyTexture(m_pbitmapTexture);
}

void Bitmap::draw()
{
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x, m_y, m_w, m_h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}
