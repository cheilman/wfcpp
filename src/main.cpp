#include <iostream>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "wfc/ImageSheet.h"
#include "stb/Image.h"

typedef struct AppState {
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    AppState *state = new AppState();
    *appstate = state;

    std::cout << "Hello, World!  From inside SDL_AppInit!" << std::endl;
    std::string prj_root = "/Users/cheilman/CLionProjects/wfcpp";
    std::string out_root = "/Users/cheilman/";
    // std::string prj_root = "C:/Users/chris/ClionProjects/wfcpp";
    // std::string out_root = "C:/Users/chris/Desktop";

    std::string tiles_path = prj_root + "/resources/tilesets/mochii-plains/tilesetPlains.png";

    auto sheet = ImageSheet::load(tiles_path, Dimensions2D(16, 16));
    std::cerr << "Loaded image sheet: " << *sheet << std::endl;
    sheet->sheet().save_png(out_root + "/tiles.png");

    auto tile = sheet->load_subimage(GridPosition(5, 4));
    std::cerr << "Sectioned image: " << *tile << std::endl;
    tile->save_png(out_root + "/section.png");

    return SDL_APP_SUCCESS;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = static_cast<AppState *>(appstate);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *state = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate) {
    AppState *state = static_cast<AppState *>(appstate);

    if (state != nullptr) {
        delete state;
        appstate = nullptr;
        state = nullptr;
    }
}
