#include "Renderer.h"

Renderer* Renderer::sInstance = NULL;

void Renderer::Draw(BitMapPack bitMapPack, SDL_Rect* destRect)
{
	if (bitMapPack.texture)
	{
		SDL_RenderCopy(m_pRenderer, bitMapPack.texture, NULL, destRect);
	}
}

Renderer* Renderer::Instance()
{
	if (sInstance == NULL)
	{
		std::cout << "Renderer Singleton not initialized with renderer!\n";
		std::cout << "Please initialize with renderer before attempting to access.\n";
		return NULL;
	}

	return sInstance;
}

Renderer* Renderer::Instance(SDL_Window* Window)
{
	if (sInstance == NULL)
	{
		std::cout << "Initializing renderer with a renderer.\n";
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


/*void Game::UpdateRenderer(void)
{
	// wipe the display to the colour we just set
	SDL_RenderClear(m_Renderer);

	// show what we've drawn
	SDL_RenderPresent(m_Renderer);
}*/