#include "game_states.hpp"
#include "static_settings.hpp"

#include <iostream>

GameStates::GameStates(sf::RenderWindow *Window_) : Window_(Window_) {
  resetGameStates();
}

void GameStates::upgrateLevel() noexcept {
  ShipMoveSpeed_ *= WeaponSpeedUpFactor_;
  BulletSpeed_ *= WeaponSpeedUpFactor_;

  AlienMoveSpeed_ *= AlienSpeedUpFactor_;

  ScorePerAlien_ *= upgrateLevelBonusFactor_;
}

void GameStates::resetGameStates() {
  Hp_ = 3;
  Score_ = 0;
  ShipMoveSpeed_ = static_settings::ShipMoveSpeed;
  BulletSpeed_ = static_settings::BulletSpeed;
  AlienMoveSpeed_ = static_settings::AlienMoveSpeed;
  ScorePerAlien_ = static_settings::ScorePerAlien;
}

void GameStates::dropHp() noexcept {
  Hp_ -= 1;
  std::cout << "You lose HP! HP: " << Hp_ << "\n";
}

void GameStates::killAlien() noexcept {
  Score_ += ScorePerAlien_;
  std::cout << "You kill Alien! Score: " << Score_ << "\n";
}