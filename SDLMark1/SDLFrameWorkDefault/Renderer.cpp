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
		Log("Rendered sprite at " + std::to_string(destRect->x) + " " + std::to_string(destRect->y), FILTHY_DEBUG);
	}
}

void Renderer::Draw(BitMapPack bitMapPack, int x_in, int y_in, SDL_Rect* srcRect)
{
	SDL_Rect* destRect = new SDL_Rect();
	destRect->x = x_in -camera->x;
	destRect->y = y_in -camera->y;
	destRect->w = bitMapPack.width;
	destRect->h = bitMapPack.height;

	Draw(bitMapPack, destRect, srcRect);

	delete destRect;
	destRect = nullptr;
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer,
		x1 - camera->x,
		y1 - camera->y,
		x2 - camera->x,
		y2 - camera->y);
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

Renderer* Renderer::Instance(SDL_Window* Window, SDL_Rect* camera, SDL_Rect* renderCamera)
{
	if (sInstance == NULL)
	{
		Log("Initializing renderer with a renderer", DEBUG);
		sInstance = new Renderer(Window);
	}
	sInstance->camera = camera;
	sInstance->renderCamera = renderCamera;
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

void Renderer::UpdateRenderer()
{
	// show what we've drawn

#ifdef RENDER_DEBUG
	
	// draw a bunch of lines
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			DrawLine(
				i * TILE_WIDTH,
				j * TILE_WIDTH,
				i * TILE_WIDTH,
				j * TILE_WIDTH + 1000);
			DrawLine(
				i * TILE_WIDTH,
				j * TILE_WIDTH,
				i * TILE_WIDTH + 1000,
				j * TILE_WIDTH);
		}
	}

#endif
	SDL_RenderSetViewport(m_pRenderer, renderCamera);
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::ClearRenderer()
{
	SDL_RenderClear(m_pRenderer);
}
