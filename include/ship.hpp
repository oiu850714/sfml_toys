#pragma once

#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "pygame-sprite-facade.hpp"

class Ship
{
public:
  Ship(sf::RenderWindow *);

  void notify(const sf::Event &);
  void update();
  void draw();

private:
  sf::RenderWindow *Window_;
  sf::Image Image_;
  sf::Texture Texture_;
  PygameSpriteFacade Sprite_;

  enum class ShipState {
    LR_Release,
    L,
    R,
    BOTH_LR,
  };

  ShipState State_ = ShipState::LR_Release;
};