#pragma once

#include <SDL.h>
namespace rendering {
	extern SDL_Window* _window;
	extern SDL_Renderer* _renderer;

	const int SCREEN_WIDTH_720 = 600;
	const int SCREEN_HEIGHT_720 = 300;
	const SDL_WindowFlags DEFAULT_WINDOW_FLAG = SDL_WINDOW_SHOWN;
	const SDL_RendererFlags DEFAULT_RENDERER_FLAG = SDL_RENDERER_TARGETTEXTURE;


	void InitRender(const char* title, int x, int y, int w, int h, Uint32 flags);
}