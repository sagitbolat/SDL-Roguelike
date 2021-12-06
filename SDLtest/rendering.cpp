#include "rendering.h"
#include "worldState.h"
#include <iostream>

namespace rendering {
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	Uint32* pixels;


	//Signiture declarations
	void WorldToPixels();
	void WorldAroundPlayerToPixels(int viewDistance, int tileSize);
	void WorldCenteredOnPlayerToPixels(int viewDistance, int tileSize, int xOffset, int yOffset);
	int createPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void DrawTileFullMap(int worldX, int worldY, int tileSize);
	int GetTileColor(int worldX, int worldY);


	//CONSTANTS
	const int DEFAULT_PIXEL_COLOR = createPixel(0, 0, 0, 255);

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

	void DisplayWorld() {
		//WorldToPixels();
		//WorldAroundPlayerToPixels(10, 8);
		WorldCenteredOnPlayerToPixels(10, 32, 304, 24);
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

	void WorldToPixels() { //NEEDS REFACTORING
		for (int x = 0; x < game::MAP_WIDTH; x++) {
			for (int y = 0; y < game::MAP_HEIGHT; y++) {
				DrawTileFullMap(x, y, TILE_SIZE);
			}
		}
	}

	void WorldAroundPlayerToPixels(int viewDistance, int tileSize){
		utils::Vector2 playerPos = game::worldState::GetPlayerLocation();
		int centerX = playerPos.x;
		int centerY = playerPos.y;
		int startX = std::fmax(0, centerX - viewDistance);
		int endX = std::fmin(game::MAP_WIDTH - 1, centerX + viewDistance);
		int startY = std::fmax(0, centerY - viewDistance);
		int endY = std::fmin(game::MAP_HEIGHT-1, centerY + viewDistance);
		for (int x = 0; x < game::MAP_WIDTH; x++) {
			for (int y = 0; y < game::MAP_HEIGHT; y++) {
				SetPixelsToColor(x * tileSize, y * tileSize, 
					(x + 1) * tileSize, 
					(y + 1) * tileSize, DEFAULT_PIXEL_COLOR);
			}
		}
		for (int x = startX; x <= endX; x++) {
			for (int y = startY; y <= endY; y++) {
				DrawTileFullMap(x, y, TILE_SIZE);
			}
		}
	}

	void WorldCenteredOnPlayerToPixels(int viewDistance, int tileSize, int xOffset, int yOffset) {
		utils::Vector2 playerPos = game::worldState::GetPlayerLocation();
		int centerX = playerPos.x;
		int centerY = playerPos.y;
		int startX = std::fmax(0, centerX - viewDistance);
		int endX = std::fmin(game::MAP_WIDTH - 1, centerX + viewDistance);
		int startY = std::fmax(0, centerY - viewDistance);
		int endY = std::fmin(game::MAP_HEIGHT - 1, centerY + viewDistance);

		//sets all tiles to black
		for (int x = 0; x < game::MAP_WIDTH; x++) {
			for (int y = 0; y < game::MAP_HEIGHT; y++) {
				SetPixelsToColor(x * TILE_SIZE, y * TILE_SIZE, 
					(x + 1) * TILE_SIZE, 
					(y + 1) * TILE_SIZE, DEFAULT_PIXEL_COLOR);
			}
		}
		//sets the tiles seen by player to be colored
		for (int x = startX; x <= endX; x++) {
			for (int y = startY; y <= endY; y++) {
				int pixelColor = GetTileColor(x, y);
				SetPixelsToColor((x-startX) * tileSize + xOffset, 
									(y - startY) * tileSize + yOffset, 
									((x - startX) + 1) * tileSize + xOffset, 
									((y - startY) + 1) * tileSize + yOffset, pixelColor);
			}
		}
	}

	void DrawTileFullMap(int worldX, int worldY, int tileSize) {
		int pixelColor = GetTileColor(worldX, worldY);
		SetPixelsToColor(worldX * tileSize, worldY * tileSize, (worldX + 1) * tileSize, (worldY + 1) * tileSize, pixelColor);

	}

	int GetTileColor(int worldX, int worldY) {
		int pixelColor = createPixel(255, 255, 255, 255);
		switch (game::worldState::GetTileType(worldX, worldY)) {
		case game::worldState::TileType::FLOOR:
			pixelColor = createPixel(250, 232, 224, 255);
			break;
		case game::worldState::TileType::WALL:
			pixelColor = createPixel(239, 124, 142, 255);
			break;
		default:
			pixelColor = DEFAULT_PIXEL_COLOR;
			break;
		}
		if (game::worldState::GetCurrentEntity(worldX, worldY) == entities::player) {
			//std::cout << "Found Player" << std::endl;
			pixelColor = createPixel(255, 0, 0, 255);
		}
		return pixelColor;
	}

	int createPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
}