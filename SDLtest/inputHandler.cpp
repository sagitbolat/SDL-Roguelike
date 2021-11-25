#include "inputHandler.h"

namespace input {

    /*
        Translates a SDL_Event into a input::Key enum and returns the enum value
    */
    Key PollInput(SDL_Event inputEvent) {

        /*switch (inputEvent.type) {
        case SDL_QUIT:
            return input::Key::QUIT;
        case SDL_KEYDOWN:
            SDL_Keycode pressed = inputEvent.key.keysym.sym;
            switch (pressed) {
            case SDLK_w:
                return Key::W;
            case SDLK_a:
                return Key::A;
            case SDLK_s:
                return Key::S;
            case SDLK_d:
                return Key::D;
            case SDLK_ESCAPE:
                return Key::ESCAPE;
            case SDLK_RETURN:
                return Key::ENTER;
            case SDLK_TAB:
                return Key::TAB;
            default:
                return Key::UNKNOWN;
            }
        case SDL_KEYUP:
            return Key::UNKNOWN;
        }*/

        if (inputEvent.type == SDL_QUIT) return input::Key::QUIT;
        else if (inputEvent.type == SDL_KEYUP) return Key::RELEASE;
        else if (inputEvent.type == SDL_KEYDOWN) {
            SDL_Keycode pressed = inputEvent.key.keysym.sym;
            switch (pressed) {
            case SDLK_w:
                return Key::W;
            case SDLK_a:
                return Key::A;
            case SDLK_s:
                return Key::S;
            case SDLK_d:
                return Key::D;
            case SDLK_ESCAPE:
                return Key::ESCAPE;
            case SDLK_RETURN:
                return Key::ENTER;
            case SDLK_TAB:
                return Key::TAB;
            default:
                return Key::UNKNOWN;
            }
        }
    }
}