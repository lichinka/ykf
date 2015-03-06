#pragma once

#include <map>
#include <string>
#include <iostream>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>



namespace ykf {

struct TextureManager {
public:
    // directory where textures are found
    const std::string DATA_DIR;

    TextureManager ( ) : DATA_DIR ("data") { }

    ~TextureManager ( ) { }

    /**
     * Loads game textures
     */
    bool load (std::string   file_name,
               std::string   id,
               SDL_Renderer* renderer) {
        auto success  = false;
        auto img_file = TextureManager::DATA_DIR + '/' +
                        file_name;
        auto img_tmp  = IMG_Load (img_file.c_str ( ));

        SDL_LogInfo (SDL_LOG_CATEGORY_APPLICATION,
                     "Loading texture file [%s]",
                     img_file.c_str ( ));

        if (img_tmp != nullptr) {
            auto texture = SDL_CreateTextureFromSurface (renderer,
                                                         img_tmp);
            if (texture != nullptr) {
                // add the loaded texture to the map
                _texture_map[id] = texture;
                SDL_FreeSurface (img_tmp);
                success = true;
            } else {
                SDL_LogError (SDL_LOG_CATEGORY_RENDER,
                              "SDL_Error: %s",
                              SDL_GetError ( ));
            }
        } else {
            SDL_LogError (SDL_LOG_CATEGORY_APPLICATION,
                          "SDL_Error: %s",
                          SDL_GetError ( ));
        }
        return success;
    }

    /**
     * Returns texture with 'id'
     */
    SDL_Texture* get (std::string id) {
        SDL_Texture* ret_value = nullptr;

        try {
            ret_value = _texture_map.at (id);
        }
        catch (std::out_of_range) {
            SDL_LogWarn (SDL_LOG_CATEGORY_APPLICATION,
                         "No texture with id [%s]",
                         id.c_str ( ));
        }
        return ret_value;
    }


private:
    std::map<std::string, SDL_Texture*> _texture_map;
};

}
