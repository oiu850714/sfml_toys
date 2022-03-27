#pragma once

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "settings.hpp"
#include "ship.hpp"
#include "pygame-sprite-facade.hpp"

class Bullet
{
public:
  Bullet(sf::RenderWindow *, const sf::Vector2f &StartPos);

  void update();
  void draw();

  sf::Vector2f getPosition() const;

private:
  sf::RenderWindow *Window_;
  sf::RectangleShape BulletShape_;
};

class Bullets
{
public:
  Bullets(sf::RenderWindow *Window, const Ship &Ship)
      : Window_(Window), Ship_(Ship) {}

  void notify(const sf::Event &);
  void update();
  void draw();

private:
  void removeOutOfBoundBullets_();
  std::vector<Bullet> BulletsInSpace_;
  sf::RenderWindow *Window_;
  const Ship &Ship_;
};