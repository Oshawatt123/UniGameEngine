#include "Renderer.h"

Renderer* Renderer::sInstance = NULL;

/*
	\brief Draws a texture on the screen

	\param bitMapPack The BitMapPack containing the texture for drawing
	\param destRect The rectangle where you intend to draw the texture on screen
	\param srcRect The rectangle within the texture you wish to draw (used for spritesheets)

*/
void Renderer::Draw(BitMapPack bitMapPack, SDL_Rect* destRect, SDL_Rect* srcRect)
{
	if (bitMapPack.texture)
	{
		SDL_RenderCopy(m_pRenderer, bitMapPack.texture, srcRect, destRect);
		Log("Rendered sprite at " + std::to_string(destRect->x) + " " + std::to_string(destRect->y), DEBUG);
	}
}

void Renderer::Draw(BitMapPack bitMapPack, int x_in, int y_in, SDL_Rect* srcRect)
{
	SDL_Rect* destRect = new SDL_Rect();
	destRect->x = x_in;
	destRect->y = y_in;
	destRect->w = bitMapPack.width;
	destRect->h = bitMapPack.height;

	Draw(bitMapPack, destRect, srcRect);
}

Renderer* Renderer::Instance()
{
	if (sInstance == NULL)
	{
		Log("Renderer Singleton not initialized with renderer!\n", ERROR);
		Log("Please initialize with renderer before attempting to access.\n", ERROR);
		return NULL;
	}

	return sInstance;
}

Renderer* Renderer::Instance(SDL_Window* Window)
{
	if (sInstance == NULL)
	{
		Log("Initializing renderer with a renderer", DEBUG);
		sInstance = new Renderer(Window);
	}
	return sInstance;
}

SDL_Renderer* Renderer::getRenderer()
{
	return m_pRenderer;
}

Renderer::Renderer(SDL_Window* Window)
{
	m_pRenderer = SDL_CreateRenderer(
		Window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!m_pRenderer)
	{
		std::cout << "RENDERER initialisation failed" << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue. Please, press it and end my AWFUL suffering" << std::endl;
		std::cin;
		return;
	}
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;
}

void Renderer::UpdateRenderer(void)
{
	// show what we've drawn
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::ClearRenderer()
{
	SDL_RenderClear(m_pRenderer);
}
