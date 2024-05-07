//
// Created by 24crickenbach on 5/7/2024.
//

#include "PromotionUI.h"

#include "System.h"

PromotionUI::PromotionUI(bool isBlack) : m_spacing(System::TILE_SIZE/3*2), m_bIsBlack(isBlack), m_padding(static_cast<float>(System::TILE_SIZE)/8, static_cast<float>(System::TILE_SIZE)/8)
{
    m_container.setFillColor(sf::Color::White);
    m_container.setSize(sf::Vector2f(System::TILE_SIZE*3/2, System::TILE_SIZE*3/2));
    m_bishopSprite.setTexture(isBlack ? System::BB_Texture : System::WB_Texture);
    m_knightSprite.setTexture(isBlack ? System::BN_Texture : System::WN_Texture);
    m_rookSprite.setTexture(isBlack ? System::BR_Texture : System::WR_Texture);
    m_queenSprite.setTexture(isBlack ? System::BQ_Texture : System::WQ_Texture);



}

PieceType PromotionUI::ManageCollision(sf::Vector2i mousePos)
{

    if(m_bishopSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        return m_bIsBlack ? BLACK_BISHOP : WHITE_BISHOP;
    }
    if(m_knightSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        return m_bIsBlack ? BLACK_KNIGHT : WHITE_KNIGHT;
    }
    if(m_rookSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        return m_bIsBlack ? BLACK_ROOK : WHITE_ROOK;
    }
    if(m_queenSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        return m_bIsBlack ? BLACK_QUEEN : WHITE_QUEEN;
    }
    return EMPTY;
}

void PromotionUI::SetUIPosition(sf::Vector2f position)
{

    m_container.setPosition(position);
    m_bishopSprite.setPosition(position + m_padding);
    m_knightSprite.setPosition(position + sf::Vector2f(m_spacing, 0) + m_padding);
    m_rookSprite.setPosition(position + sf::Vector2f(0, m_spacing) + m_padding);
    m_queenSprite.setPosition(position + sf::Vector2f(m_spacing, m_spacing) + m_padding);
}

void PromotionUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_container);
    target.draw(m_bishopSprite);
    target.draw(m_knightSprite);
    target.draw(m_rookSprite);
    target.draw(m_queenSprite);
}
