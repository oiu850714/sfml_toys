#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "aliens.hpp"
#include "bullets.hpp"
#include "game_states.hpp"
#include "ship.hpp"

class SpaceInvaders {
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
  void checkCollisions_();
  void resetBattleField_();

  bool Done_ = false;
  sf::Clock Clock_;
  sf::RenderWindow Window_;
  GameStates GameStates_;
  Ship Ship_;
  Bullets Bullets_;
  Aliens Aliens_;
};
