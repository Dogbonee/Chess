//
// Created by 24crickenbach on 5/7/2024.
//

#ifndef PROMOTIONUI_H
#define PROMOTIONUI_H

#include <SFML/Graphics.hpp>

#include "ChessBoard.h"

class PromotionUI : public sf::Drawable {

    bool m_bIsBlack;

    sf::RectangleShape m_container;

    sf::Sprite m_knightSprite;
    sf::Sprite m_bishopSprite;
    sf::Sprite m_rookSprite;
    sf::Sprite m_queenSprite;

    float m_spacing;
    sf::Vector2f m_padding;

public:
    PromotionUI(bool isBlack);

    PieceType ManageCollision(sf::Vector2i mousePos);

    void SetUIPosition(sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



#endif //PROMOTIONUI_H
