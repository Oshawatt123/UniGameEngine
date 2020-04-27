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
	static Renderer* sInstance; /*!< Static instance of the Renderer class. */

	SDL_Renderer* m_pRenderer; /*!< The SDL_Renderer which does all the heavy lifting.*/
	Vector2 RenderOffset; /*!< The offset applied to all things being rendered in game-mode. Allows for movement around a scene with the camera following. Or at least, the illusion of.*/
	Vector2 EditorRenderOffset; /*!< The offset applied to all things being rendererd in edit-mode. Allows for a reasonable editor.*/

	std::vector<Line> EditorRenderLines; /*!< A vector that stores all lines to be drawn this frame.*/

	float scale = 5; /*!< Scale to be applied to all objects in game-view on top of any they have themselves. Allows for camera zoom.*/
	float editorScale = 3; /*!< Scale to be applied to all objects in edit-view on top of any they have themselves. Allows for camera zoom.*/

public:

	/*!
		Method for getting an instance of Renderer.
	*/
	static Renderer* Instance();

	/*!
		The renderer requires a Window, so this must be called first as an initialization.

		\param[in] Window Reference to the SDL_Window that we want to render onto.
	*/
	static Renderer* Instance(SDL_Window* Window);

	/*!
		Base draw function. Draws a bitmap to a point on the screen.

		\param[in] bitMapPack	The BitMapPack to draw to the screen.
		\param[in] destRect		The location to draw the bitmap, as well as size information for how big it should be.
		\param[in] srcRect		The clip of the bitmap we want to render. Used for indexing into sprite-sheets. NULL assumes no clip; drawing the whole bitmap.
	*/
	void Draw(BitMapPack bitMapPack, SDL_Rect* destRect, SDL_Rect* srcRect = NULL);

	/*!
		Override draw function. Draws a bitmap to a point on the screen (x,y) with scale modification.

		\param[in] bitMapPack	The BitMapPack to draw to the screen.
		\param[in] x			The x position to draw the bitmap in world-space.
		\param[in] y			The y position to draw the bitmap in world-space.
		\param[in] scale		The scale to apply to the object.
		\param[in] srcRect		The clip of the bitmap we want to render. Used for indexing into sprite-sheets. NULL assumes no clip; drawing the whole bitmap.
	*/
	void Draw(BitMapPack bitMapPack, int x, int y, float scale = 1, SDL_Rect* srcRect = NULL);

	/*!
		Override draw function. Draws a bitmap to a point on the screen (x,y) with scale modification.

		\param[in] bitMapPack	The BitMapPack to draw to the screen.
		\param[in] x			The x position to draw the bitmap in world-space.
		\param[in] y			The y position to draw the bitmap in world-space.
		\param[in] index		The index into the spritesheet that we want to render. Index uses the TILE_WIDTH macro defined in EngineStructs. Make sure this is set to the sprite size you want.
		\param[in] scale		The scale to apply to the object
	*/
	void Draw(BitMapPack bitMapPack, int x, int y, int index, float scale = 1);

	/*!
		Adds a line to the EditorRenderLines vector. These are batch-drawn at the end of the frame in UpdateRenderer.

		\param[in] x1		Start X position of the line.
		\param[in] y1		Start y position of the line.
		\param[in] x2		End X position of the line.
		\param[in] y2		End X position of the line.
		\param[in] color	The color of the line. Black by default.
	*/
	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color = { 0,0,0,255 });

	/*!
		This function sets the render offset for game-view.

		\param[in] renderOffset The new renderOffset.
	*/
	void SetRenderOffset(Vector2 renderOffset);
#
	/*!
		This function sets the render offset for game-view.

		\param[in] x	The new renderOffset x value.
		\param[in] y	The new renderOffset y value.
	*/
	void SetRenderOffset(int x, int y);

	/*!
		Gets the render offset of the game-view camera.

		\return the render offset of the game-view camera.
	*/
	Vector2 getRenderOffset();

	/*!
		Translates the Edit-view renderOffset. This uses translation rather than a position assignment due to the nature of the input moving the camera.
		The input is taken as mouse movement delta so there is no need to add an extra step in between.

		\param[in] translation The value to translate the editor camera by.
	*/
	void TranslateEditorCamera(Vector2 translation);


	/*!
		Override function for TranslateEditorCamera that takes two int's instead of a vector2.

		\param[in] x	The x value to translate the camera by.
		\param[in] y	The y value to translate the camera by.
	*/
	void TranslateEditorCamera(int x, int y);

	/*!
		Gets the offset of the editor camera.

		\return The offset of the editor camera.
	*/
	Vector2 GetEditorCamera();

	/*!
		A QoL function to change a screen-space co-ordinate to a world-space co-ordinate in edit-view.

		\param[in] screenSpace	A position in screen space.

		\return					The corresponding position in world-space using the editor camera.
	*/
	Vector2 screenToEditorWorldSpace(Vector2 screenSpace);

	/*!
		A QoL function to get reference to the renderer for use in other classes which may need it in certain SDL functions.

		\return a reference to the SDL_Renderer used by the renderer.
	*/
	SDL_Renderer* getRenderer();

	/*!
		A method to get the scale of the game-view camera.

		\return The scale of the game-view camera.
	*/
	float getScale();

	/*!
		A method to get the scale of the edit-view camera.

		\return The scale of the edit-view camera.
	*/
	float getEditorScale();

	/*!
		Updates the renderer.

		This function presents all bitmaps drawn this frame to the screen.

		It also batch-draws all the lines passed in this frame. This ensures they will render over the top of everything.
		This functionality is wanted as their use is for edit-mode and debugging.
	*/
	void UpdateRenderer();

	/*!
		Clears the renderer ready for the next frame of draw calls.
	*/
	void ClearRenderer();

private:

	/*!
		Creates a renderer with an SDL_Window.
	*/
	Renderer(SDL_Window* Window);

	~Renderer();
};