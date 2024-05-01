//
// Created by 24crickenbach on 5/1/2024.
//

#include "System.h"

void System::LoadResources()
{
    WP_Texture.loadFromFile("../assets/Chess_Pieces/WP.png");
    WN_Texture.loadFromFile("../assets/Chess_Pieces/WN.png");
    WB_Texture.loadFromFile("../assets/Chess_Pieces/WB.png");
    WR_Texture.loadFromFile("../assets/Chess_Pieces/WR.png");
    WQ_Texture.loadFromFile("../assets/Chess_Pieces/WQ.png");
    WK_Texture.loadFromFile("../assets/Chess_Pieces/WK.png");
    BP_Texture.loadFromFile("../assets/Chess_Pieces/BP.png");
    BN_Texture.loadFromFile("../assets/Chess_Pieces/BN.png");
    BB_Texture.loadFromFile("../assets/Chess_Pieces/BB.png");
    BR_Texture.loadFromFile("../assets/Chess_Pieces/BR.png");
    BQ_Texture.loadFromFile("../assets/Chess_Pieces/BQ.png");
    BK_Texture.loadFromFile("../assets/Chess_Pieces/BK.png");

    Arrow_Cursor.loadFromSystem(sf::Cursor::Arrow);
    Hand_Cursor.loadFromSystem(sf::Cursor::Hand);
}
