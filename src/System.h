//
// Created by 24crickenbach on 5/1/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Cursor.hpp>


class System {

public:
    //constants for now but in the future they will be variable
    static constexpr int SCREEN_WIDTH = 1920;
    static constexpr int SCREEN_HEIGHT = 1080;

    static constexpr int TILE_SIZE = SCREEN_HEIGHT/8;
    static constexpr int X_CENTER_OFFSET = SCREEN_WIDTH/2 - TILE_SIZE * 4;

    static inline sf::Texture WP_Texture;
    static inline sf::Texture WN_Texture;
    static inline sf::Texture WR_Texture;
    static inline sf::Texture WB_Texture;
    static inline sf::Texture WQ_Texture;
    static inline sf::Texture WK_Texture;
    static inline sf::Texture BP_Texture;
    static inline sf::Texture BK_Texture;
    static inline sf::Texture BR_Texture;
    static inline sf::Texture BB_Texture;
    static inline sf::Texture BQ_Texture;
    static inline sf::Texture BN_Texture;

    static inline sf::Cursor Arrow_Cursor;
    static inline sf::Cursor Hand_Cursor;

    static void LoadResources();
};



#endif //SYSTEM_H
