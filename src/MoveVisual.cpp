//
// Created by hunde on 5/7/2024.
//

#include "MoveVisual.h"

MoveVisual::MoveVisual(const sf::Vector2i& boardPos) : m_boardPosition(boardPos)
{

    m_moveVisual.setRadius(10);
    m_moveVisual.setOrigin(m_moveVisual.getRadius(), m_moveVisual.getRadius());
    m_moveVisual.setPosition(boardPos.x * System::TILE_SIZE + System::X_CENTER_OFFSET + System::TILE_SIZE/2, boardPos.y * System::TILE_SIZE + System::TILE_SIZE/2);
    m_moveVisual.setFillColor(sf::Color(135,206,250, 200));

    m_activationRect = sf::FloatRect(boardPos.x * System::TILE_SIZE + System::X_CENTER_OFFSET, boardPos.y * System::TILE_SIZE, System::TILE_SIZE, System::TILE_SIZE);


}

sf::Vector2i MoveVisual::GetBoardCoordinates()
{
    return m_boardPosition;
}

bool MoveVisual::IsOverlapping(const sf::Vector2i &mousePos)
{
    return m_activationRect.contains(sf::Vector2f(mousePos.x, mousePos.y));
}


void MoveVisual::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_moveVisual);
}
