#include "game.h"
#include "rendering.h"
#include "inputHandler.h"
#include "SDL_Main.h"
#include <iostream>
#include <ctime>


const char* TITLE = "Game";
void InitEverything();
void GameLoop();
input::Key GetInput();

input::Key lastInput;


int main(int argc, char** argv) {
    
    //INIT
    InitEverything();


    //GAMELOOP
    GameLoop();

    //DEALLOC
    game::DeallocWorld();
    delete[] rendering::pixels;
    SDL_DestroyTexture(rendering::_texture);
    SDL_DestroyRenderer(rendering::_renderer);
    return 0;
}

void InitEverything() {
    //initialize input handler
    //input::InitInput();
    //initialize game
    game::InitGame();
    //initialize renderer
    rendering::InitRender(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rendering::SCREEN_WIDTH_720, rendering::SCREEN_HEIGHT_720, rendering::DEFAULT_WINDOW_FLAG);
}

void GameLoop() {
    clock_t timer; //for measuring loop runtime
    while (game::gameState != game::GameState::GAME_QUIT) {
        timer = clock(); //start timer

        //Process input
        input::Key input = GetInput();

        //THE CONTINUE BLOCK IS MEANT TO ENSURE THAT KEY EVENTS ARE ONLY FIRED ONCE PER KEYPRESS.

        //if Key is unknown, skip the rest of the loop
        if (input == input::Key::UNKNOWN) continue;
        //if Keystate did not change, skip rest of the loop
        if (input == lastInput) continue;
        //if Keystate is Key Released, update input and continue
        if (input == input::Key::RELEASE) {
            lastInput = input;
            continue;
        } else if (input == input::Key::QUIT) {
            game::gameState = game::GameState::GAME_QUIT;
            continue;
        }


        //Do game logic based on input
        game::UpdateWorld(input);
        //Render gameworld
        rendering::DisplayWorld();
        //std::cout << "UPDATED WORLD" << std::endl;
        lastInput = input;

        timer = clock() - timer;
        std::cout << "One game loop took: " << (double)timer/CLOCKS_PER_SEC << " seconds" << std::endl;
    }
}

input::Key GetInput() {
    SDL_Event input;
    SDL_PollEvent(&input);
    return input::PollInput(input);
}



