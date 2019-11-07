#pragma once

#include <string>
#include "EngineStructs.h"

struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{
private:
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	int m_x, m_y;
	int m_w, m_h;

public:
	Bitmap(SDL_Renderer* renderer, int xPos, int yPos, BitMapPack bmpPack);
	~Bitmap();

	void draw();
};

