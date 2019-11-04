#pragma once

#include <string>
#include "EngineStructs.h"

struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{
private:
	SDL_Texture* m_pbitmapTexture;

	int m_x, m_y;
	int m_w, m_h;

public:
	Bitmap(int xPos, int yPos, BitMapPack bmpPack);
	~Bitmap();
};

