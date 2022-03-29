#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameStates {
public:
  GameStates(sf::RenderWindow *Window);
  void upgrateLevel() noexcept;
  void dropHp() noexcept;
  void killAlien() noexcept;
  void draw();

  auto getShipSpeed() const noexcept { return ShipMoveSpeed_; }
  auto getBulletSpeed() const noexcept { return BulletSpeed_; }
  auto getAlienMoveSpeed() const noexcept { return AlienMoveSpeed_; }

  void resetGameStates();

  bool isDead() const noexcept { return Hp_ == 0; }

private:
  sf::RenderWindow *Window_;
  int Hp_;
  int Score_;

  float ShipMoveSpeed_;
  float BulletSpeed_;

  // Only keep moving speed increase; making drop speed increasing is too dark
  // soul.
  float AlienMoveSpeed_;

  float ScorePerAlien_;

  const float upgrateLevelBonusFactor_ = 1.1f;
  const float AlienSpeedUpFactor_ = 1.15f;
  const float WeaponSpeedUpFactor_ = 1.17f;
};
