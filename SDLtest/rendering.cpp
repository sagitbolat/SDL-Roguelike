#include "rendering.h"
#include <iostream>

namespace rendering {
	const int TILE_SIZE = 16;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	Uint32* pixels;


	//Signiture declarations
	void WorldToPixels(game::WorldState state);
	int createPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);



	void rendering::InitRender(const char* title, int x, int y, int w, int h, Uint32 flags) {
		SDL_Init(SDL_INIT_EVERYTHING);

		//initalize SDL components
		_window = SDL_CreateWindow(title, x, y, w, h, flags);

		_renderer = SDL_CreateRenderer(rendering::_window, -1, 0);

		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH_720, SCREEN_HEIGHT_720);
		

		//initialize pixels array
		pixels = new Uint32[SCREEN_HEIGHT_720 * SCREEN_WIDTH_720];
		
		//Set the inital texture to all black.
		memset(pixels, 0, SCREEN_HEIGHT_720 * SCREEN_WIDTH_720 * sizeof(Uint32));
		
		SDL_UpdateTexture(_texture, NULL, pixels, SCREEN_WIDTH_720 * sizeof(Uint32));
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, NULL, NULL);
		SDL_RenderPresent(_renderer);

		//std::cout << "Initialized Texture" << std::endl;
	}

	void DisplayWorld(game::WorldState state) {
		WorldToPixels(state);

		SDL_UpdateTexture(_texture, NULL, pixels, SCREEN_WIDTH_720 * sizeof(Uint32));
		//std::cout << "Updated Texture" << std::endl;
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, NULL, NULL);
		SDL_RenderPresent(_renderer);
	}
	
	void SetPixelsToColor(int xMin, int yMin, int xMax, int yMax, int color) {
		for (int x = xMin; x < xMax; x++) {
			for (int y = yMin; y < yMax; y++) {
				if (y * SCREEN_WIDTH_720 + x >= SCREEN_HEIGHT_720 * SCREEN_WIDTH_720) throw "Tried drawing outside of screen";
				pixels[y * SCREEN_WIDTH_720 + x] = color;
			}
		}
	}

	void WorldToPixels(game::WorldState state) {
		for (int x = 0; x < game::MAP_WIDTH; x++) {
			for (int y = 0; y < game::MAP_HEIGHT; y++) {
				int pixelColor;
				if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1)) pixelColor = createPixel(250, 232, 224, 255);
				else pixelColor = createPixel(239, 124, 142, 255);
				SetPixelsToColor(x * TILE_SIZE, y * TILE_SIZE, (x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE, pixelColor);
			}
		}
	}

	void DrawAsciiChar() {

	}

	int createPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
}