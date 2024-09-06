#include <iostream>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <vector>

#include "wfc/ImageSheet.h"

typedef struct AppState {
    std::vector<std::pair<SDL_Window *, SDL_Renderer *>> windows_and_renders;
    std::unique_ptr<ImageSheet> imageSheet;

    AppState() : imageSheet(nullptr) {}

    ~AppState() {
        for (auto wr : windows_and_renders) {
            auto window = wr.first;
            auto render = wr.second;

            if (window != nullptr) {
                SDL_DestroyWindow(window);
            }

            if (render != nullptr) {
                SDL_DestroyRenderer(render);
            }
        }
    }
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    auto state = new AppState();
    *appstate = state;

    std::cout << "Hello, World!  From inside SDL_AppInit!" << std::endl;
    // std::string prj_root = "/Users/cheilman/CLionProjects/wfcpp";
    // std::string out_root = "/Users/cheilman/";
    std::string prj_root = "C:/Users/chris/ClionProjects/wfcpp";
    std::string out_root = "C:/Users/chris/Desktop";

    std::string tiles_path = prj_root + "/resources/tilesets/mochii-plains/tilesetPlains.png";

    state->imageSheet = ImageSheet::load(tiles_path, Dimensions2D(16, 16));

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL subsystem: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    state->windows_and_renders.emplace_back(state->imageSheet->sheet().display());

    auto shroom = state->imageSheet->sheet().cropy(GridPosition(16 * 8, 16 * 5), Dimensions2D(16, 16));

    state->windows_and_renders.emplace_back(shroom->display());

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

    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
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
