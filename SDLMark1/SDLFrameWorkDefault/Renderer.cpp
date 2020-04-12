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
	if (!blackboard->EditMode)
	{
		destRect->x = (x_in * scale) - RenderOffset.x;
		destRect->y = (y_in * scale) - RenderOffset.y;
		destRect->w = TILE_WIDTH * scale;
		destRect->h = TILE_WIDTH * scale;
	}
	else
	{
		destRect->x = (x_in * editorScale) - EditorRenderOffset.x;
		destRect->y = (y_in * editorScale) - EditorRenderOffset.y;
		destRect->w = TILE_WIDTH * editorScale;
		destRect->h = TILE_WIDTH * editorScale;
	}

	Draw(bitMapPack, destRect, srcRect);

	delete destRect;
	destRect = nullptr;

}

void Renderer::Draw(BitMapPack bitMapPack, int x, int y, int index)
{
	SDL_Rect* srcRect = new SDL_Rect();

	srcRect->x = 0 + (TILE_WIDTH * index);
	srcRect->y = 0;
	srcRect->w = TILE_WIDTH;
	srcRect->h = TILE_WIDTH;

	Draw(bitMapPack, x, y, srcRect);

	delete srcRect;
	srcRect = nullptr;
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
	EditorRenderLines.push_back(Line(x1, y1, x2, y2, color));
}

void Renderer::SetRenderOffset(Vector2 renderOffset)
{
	RenderOffset = renderOffset;
}

void Renderer::SetRenderOffset(int x, int y)
{
	SetRenderOffset(Vector2(x, y));
}

void Renderer::TranslateEditorCamera(Vector2 translation)
{
	EditorRenderOffset -= translation;
}

void Renderer::TranslateEditorCamera(int x, int y)
{
	TranslateEditorCamera(Vector2(x, y));
}

Vector2 Renderer::GetEditorCamera()
{
	return EditorRenderOffset;
}

Vector2 Renderer::screenToEditorWorldSpace(Vector2 screenSpace)
{
	Vector2 worldSpace;

	worldSpace = screenSpace + EditorRenderOffset;
	worldSpace /= editorScale;

	return worldSpace;
}

Renderer* Renderer::Instance()
{
	if (sInstance == NULL)
	{
		Log("Renderer Singleton not initialized with renderer!\n", DBERROR);
		Log("Please initialize with renderer before attempting to access.\n", DBERROR);
		return NULL;
	}

	return sInstance;
}
SDL_Window* renderWindow;
Renderer* Renderer::Instance(SDL_Window* Window)
{
	renderWindow = Window;
	if (sInstance == NULL)
	{
		Log("Initializing renderer with a renderer", DEBUG);
		sInstance = new Renderer(renderWindow);
	}
	return sInstance;
}

SDL_Renderer* Renderer::getRenderer()
{
	return m_pRenderer;
}

float Renderer::getScale()
{
	return scale;
}

float Renderer::getEditorScale()
{
	return editorScale;
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
	//SDL_RenderSetViewport(m_pRenderer, renderCamera);

	// draw all the editor lines
	for (Line line : EditorRenderLines)
	{
		SDL_SetRenderDrawColor(m_pRenderer, line.color.r, line.color.g, line.color.b, line.color.a);
		SDL_RenderDrawLine(m_pRenderer,
			line.start.x * editorScale - EditorRenderOffset.x,
			line.start.y * editorScale - EditorRenderOffset.y,
			line.end.x * editorScale - EditorRenderOffset.x,
			line.end.y * editorScale - EditorRenderOffset.y);
	}
	EditorRenderLines.clear();

	SDL_RenderPresent(m_pRenderer);
}

void Renderer::ClearRenderer()
{
	SDL_SetRenderDrawColor(m_pRenderer, 114, 144, 154, 255);
	SDL_RenderClear(m_pRenderer);
}