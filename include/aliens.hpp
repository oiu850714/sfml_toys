#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "bullets.hpp"
#include "pygame-sprite-facade.hpp"
#include "ship.hpp"

class Alien {
public:
  static auto getScaledFactor() { return 2; }
  Alien(sf::RenderWindow *, const sf::Texture &AlienTexture,
        const sf::Vector2f &StartPos);
  void update();
  void draw();

  sf::Vector2f getPosition() const { return Sprite_.getCenter(); }
  bool isReachingBoundary() const;
  // Make Alien drop downward the window.
  void drop();
  bool isShooted(const sf::Vector2f &ShootPos) const;

private:
  sf::RenderWindow *Window_;
  PygameSpriteFacade Sprite_;
};

class Aliens {
public:
  static int getAlienMoveDirection() { return AlienMoveDirection_; }

  Aliens(sf::RenderWindow *);
  void update();
  void draw();

  void removeShootedAliens(const std::vector<Bullet> &);
  bool killedSpaceShip(const Ship &Ship) const;

  void createNewAliens();

private:
  bool isAliensReachingBoundary_() const;
  void dropAliens_();
  sf::RenderWindow *Window_;

  std::vector<Alien> RemainAliens_;
  sf::Image AlienImage_;
  sf::Texture AlienTexture_;

  static int AlienMoveDirection_;
};