#pragma once
#include<SFML/Graphics.hpp>


enum class PieceType {
    ROOK,
    BISHOP,
    KING,
    QUEEN,
    PAWN,
    HORSE
};


#define vec2u sf::Vector2u

#define vec2f sf::Vector2f

#define BLACK sf::Color(51, 44, 80)

#define WHITE sf::Color(70, 135, 143)

#define WHITE_PIECE sf::Color(200, 200, 200)

#define BLACK_PIECE sf::Color(0, 30, 100)


namespace TEXTURES {
    const auto PAWN = "assets/pawn.png";
    const auto BISHOP = "assets/bishop.png";
    const auto KING = "assets/king.png";
    const auto HORSE = "assets/horse.png";
    const auto QUEEN = "assets/queen.png";
    const auto ROOK = "assets/rook.png";
}
