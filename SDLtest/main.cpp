#include "game.h"
#include "rendering.h"
#include "inputHandler.h"
#include <iostream>


const char* TITLE = "Game";
void InitEverything();
void GameLoop();
input::Key GetInput();

input::Key lastInput;


int main(int argc, char** argv) {
    InitEverything();

    GameLoop();
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
    while (game::gameState != game::GameState::GAME_QUIT) {
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
        }


        //Do game logic based on input
        game::WorldState state = game::GetUpdatedWorld(input);
        std::cout << "UPDATED WORLD" << std::endl;
        //Render gameworld

        lastInput = input;
    }
}

input::Key GetInput() {
    SDL_Event input;
    if (SDL_PollEvent(&input) == 1)
    //SDL_PollEvent(&input);
        return input::PollInput(input);
    else return input::Key::RELEASE;
}



