#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "pygame-sprite-facade.hpp"

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
  void setGameStatesTextProperties_();
  void updateScoreText_();
  void updateBestScoreText_();
  void updateCurrentLevelText_();

  void drawHp_();
  void drawStatistics_();

  sf::RenderWindow *Window_;
  int Hp_;
  sf::Image ShipHpImage_;
  sf::Texture ShipHpTexture_;
  PygameSpriteFacade ShipHpSprite_;

  sf::Font DigitFont_;
  int Score_;
  int BestScore_ = 0;
  int CurrentLevel_ = 1;
  sf::Text ScoreText_;
  sf::Text BestScoreText_;
  sf::Text CurrentLevelText_;

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
