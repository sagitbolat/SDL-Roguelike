#include "rendering.h"
namespace rendering {
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	void rendering::InitRender(const char* title, int x, int y, int w, int h, Uint32 flags) {
		SDL_Init(SDL_INIT_EVERYTHING);

		_window = SDL_CreateWindow(title, x, y, w, h, flags);

		_renderer = SDL_CreateRenderer(rendering::_window, -1, 0);
	}
}