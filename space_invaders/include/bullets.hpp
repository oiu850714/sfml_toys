#pragma once

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "pygame-sprite-facade.hpp"
#include "ship.hpp"
#include "static_settings.hpp"

class Bullet {
public:
  static auto getScaledFactor() { return 2; }
  Bullet(sf::RenderWindow *, const sf::Texture &BulletTexture,
         const sf::Vector2f &StartPos);

  void update(float BulletSpeed);
  void draw();

  sf::Vector2f getPosition() const;

private:
  sf::RenderWindow *Window_;
  PygameSpriteFacade Sprite_;
};

class Bullets {
public:
  Bullets(sf::RenderWindow *Window, const Ship &Ship,
          const GameStates &GameStates);

  void notify(const sf::Event &);
  void update();
  void draw();

  const std::vector<Bullet> &getBulletData() const { return BulletsInSpace_; }

  void clear();

private:
  void removeOutOfBoundBullets_();
  std::vector<Bullet> BulletsInSpace_;
  sf::RenderWindow *Window_;
  const GameStates &GameStates_;
  const Ship &Ship_;

  sf::Image BulletImage_;
  sf::Texture BulletTexture_;
};