#pragma once

#include "pygame-sprite-facade.hpp"

#include <SFML/System/Vector2.hpp>

// TODO: Make first arg another Sprite and use AABB detection instead.
bool isInSprite(const sf::Vector2f &Coord, const PygameSpriteFacade &Sprite);