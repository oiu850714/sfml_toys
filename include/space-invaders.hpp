#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ship.hpp"
#include "bullets.hpp"

class SpaceInvaders
{
public:
  SpaceInvaders();
  ~SpaceInvaders();

  bool isDone();
  void handleInput();
  void update();
  void render();

private:
  void notify_(const sf::Event &);
  void quitGame_();

  bool Done_ = false;
  sf::Clock Clock_;
  sf::RenderWindow Window_;
  Ship Ship_;
  Bullets Bullets_;
};
