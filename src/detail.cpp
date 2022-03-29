#include "detail.hpp"

bool isInSprite(const sf::Vector2f &Coord, const PygameSpriteFacade &Sprite) {
  return Sprite.getMidLeft().x <= Coord.x &&
         Sprite.getMidRight().x >= Coord.x && Sprite.getTopMid().y <= Coord.y &&
         Sprite.getBottomMid().y >= Coord.y;
}