//
// Created by hunde on 5/7/2024.
//

#ifndef MOVEVISUAL_H
#define MOVEVISUAL_H

#include <SFML/Graphics.hpp>
#include "System.h"

class MoveVisual : public sf::Drawable {

    sf::Vector2i m_boardPosition;
    sf::CircleShape m_moveVisual;
    sf::FloatRect m_activationRect;

public:
    MoveVisual(const sf::Vector2i& boardPos);

    sf::Vector2i GetBoardCoordinates();
    bool IsOverlapping(const sf::Vector2i& mousePos);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



#endif //MOVEVISUAL_H
