#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "pygame-sprite-facade.hpp"

class Alien
{
public:
  static auto getScaledFactor() { return 2; }
  Alien(sf::RenderWindow *, const sf::Texture &AlienTexture, const sf::Vector2f &StartPos);
  void update();
  void draw();

  bool isReachingBoundary() const;
  // Make Alien drop downward the window.
  void drop();

private:
  sf::RenderWindow *Window_;
  PygameSpriteFacade Sprite_;
};

class Aliens
{
public:
  static int getAlienMoveDirection() { return AlienMoveDirection_; }

  Aliens(sf::RenderWindow *);
  void update();
  void draw();

private:
  bool isAliensReachingBoundary_() const;
  void dropAliens_();
  sf::RenderWindow *Window_;

  std::vector<Alien> RemainAliens_;
  sf::Image AlienImage_;
  sf::Texture AlienTexture_;

  static int AlienMoveDirection_;
};