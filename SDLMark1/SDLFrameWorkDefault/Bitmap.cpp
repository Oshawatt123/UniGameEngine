#include "Bitmap.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_render.h"

Bitmap::Bitmap(int xPos, int yPos, BitMapPack bmpPack)
{
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