#include "game.h"
#include "rendering.h"
#include "inputHandler.h"
#include "SDL_Main.h"
#include <iostream>
#include <ctime>

const double KEY_REPEAT_RATE = 0.1;

const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
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
    clock_t timeofLastKeyRepitition = clock();

    while (game::gameState != game::GameState::GAME_QUIT) {
        timer = clock(); //start timer

        bool isShiftPressed = keyboardState[SDL_SCANCODE_LSHIFT]; //checks whether shift is pressed down

        //Process input
        input::Key input = GetInput();

        double timeSinceLastKeyRepitition = (double)((double)clock() - timeofLastKeyRepitition)/ CLOCKS_PER_SEC;
        //if shift is pressed and some time has passed from previous fire of this if block, Handle game input.
        if (isShiftPressed && timeSinceLastKeyRepitition > KEY_REPEAT_RATE) {
            game::HandleInput(input);
            timeofLastKeyRepitition = clock();
        }
        //if Key is not unknown or if Keystate changed, Handle game input.
        if (input != lastInput && input != input::Key::UNKNOWN) {
            //Do game logic based on input
            game::HandleInput(input);
        }
        //if Keystate is Key Released, update input and continue
        if (input == input::Key::RELEASE) {
            lastInput = input;
        } else if (input == input::Key::QUIT) {
            game::gameState = game::GameState::GAME_QUIT;
            break; //quit out of gameloop
        }

        //Update gameworld with any passive processes
        //game::UpdateWorld();

        //Render gameworld
        rendering::DisplayWorld();
        //std::cout << "UPDATED WORLD" << std::endl;
        lastInput = input;

        timer = clock() - timer;
        //std::cout << "One game loop took: " << (double)timer/CLOCKS_PER_SEC << " seconds" << std::endl;
    }
}

input::Key GetInput() {
    SDL_Event input;
    SDL_PollEvent(&input);
    return input::PollInput(input);
}



