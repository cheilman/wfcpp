#include <iostream>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "wfc/ImageSheet.h"

typedef struct AppState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::unique_ptr<ImageSheet> imageSheet;

    AppState() : window(nullptr), renderer(nullptr), imageSheet(nullptr) {}

    ~AppState() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    auto state = new AppState();
    *appstate = state;

    std::cout << "Hello, World!  From inside SDL_AppInit!" << std::endl;
    std::string prj_root = "/Users/cheilman/CLionProjects/wfcpp";
    std::string out_root = "/Users/cheilman/";
    // std::string prj_root = "C:/Users/chris/ClionProjects/wfcpp";
    // std::string out_root = "C:/Users/chris/Desktop";

    std::string tiles_path = prj_root + "/resources/tilesets/mochii-plains/tilesetPlains.png";

    state->imageSheet = ImageSheet::load(tiles_path, Dimensions2D(16, 16));

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL subsystem: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "An image!");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, state->imageSheet->sheet().width() * 4);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, state->imageSheet->sheet().height() * 4);
    state->window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    if (!state->window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        delete state;
        *appstate = nullptr;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return SDL_APP_FAILURE;
    }

    state->renderer = SDL_CreateRenderer(state->window, "software");
    if (!state->renderer) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        delete state;
        *appstate = nullptr;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);
    state->imageSheet->sheet().display_on(*state->renderer);
    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    auto state = static_cast<AppState *>(appstate);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    auto state = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate) {
    auto state = static_cast<AppState *>(appstate);

    if (state != nullptr) {
        delete state;
        appstate = nullptr;
        state = nullptr;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
