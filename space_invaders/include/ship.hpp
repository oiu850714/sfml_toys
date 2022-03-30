#pragma once

#include <cassert>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "game_states.hpp"
#include "pygame-sprite-facade.hpp"
#include "static_settings.hpp"

class Ship {
public:
  Ship(sf::RenderWindow *, const GameStates &);

  void notify(const sf::Event &);
  void update();
  void draw();

  bool isCollided(const sf::Vector2f &) const;
  void reborn();

  sf::Vector2f getShipMozzlePos() const;

private:
  sf::RenderWindow *Window_;
  const GameStates &GameStates_;
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