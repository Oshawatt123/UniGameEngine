#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "EngineStructs.h"
#include "Logger.h"
#include "MathHelper.h"
#include "BlackBoard.h"


#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <Gl\gl3w.h>

class Renderer
{

public:

private:
	static Renderer* sInstance;

	SDL_Renderer* m_pRenderer;
	Vector2 RenderOffset;
	Vector2 EditorRenderOffset;

	std::vector<Line> EditorRenderLines;

	float scale = 5;
	float editorScale = 3;

public:

	static Renderer* Instance();

	static Renderer* Instance(SDL_Window* Window);


	void Draw(BitMapPack bitMapPack, SDL_Rect* destRect, SDL_Rect* srcRect = NULL);

	void Draw(BitMapPack bitMapPack, int x, int y, float scale = 1, SDL_Rect* srcRect = NULL);

	void Draw(BitMapPack bitMapPack, int x, int y, int index, float scale = 1);

	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color = { 0,0,0,255 });

	void SetRenderOffset(Vector2 renderOffset);

	void SetRenderOffset(int x, int y);

	Vector2 getRenderOffset();

	void TranslateEditorCamera(Vector2 translation);

	void TranslateEditorCamera(int x, int y);

	Vector2 GetEditorCamera();

	Vector2 screenToEditorWorldSpace(Vector2 screenSpace);

	SDL_Renderer* getRenderer();

	float getScale();
	float getEditorScale();

	void UpdateRenderer();

	void ClearRenderer();

private:
	Renderer(SDL_Window* Window);

	~Renderer();
};