//
// Created by dawud on 23/07/2025.
//

#include "FontManager.h"
#include <stdexcept>

sf::Font& getSharedFont() {
    static sf::Font font;
    static bool loaded = false;

    if (!loaded) {
        if (!font.loadFromFile("assets/fonts/Roboto-Light.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
        loaded = true;
    }

    return font;
}
