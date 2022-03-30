#include "game_states.hpp"
#include "static_settings.hpp"

#include <sstream>

GameStates::GameStates(sf::RenderWindow *Window_) : Window_(Window_) {
  DigitFont_.loadFromFile(static_settings::ArialFontPath);
  ShipHpImage_.loadFromFile(static_settings::ShipImagePath);
  ShipHpTexture_.loadFromImage(ShipHpImage_);
  ShipHpSprite_.setSFSprite(sf::Sprite(ShipHpTexture_));

  setGameStatesTextProperties_();

  resetGameStates();
}

void GameStates::setGameStatesTextProperties_() {
  ScoreText_.setFont(DigitFont_);
  ScoreText_.setFillColor(sf::Color::Black);
  ScoreText_.setCharacterSize(30);
  BestScoreText_.setFont(DigitFont_);
  BestScoreText_.setStyle(sf::Text::Bold);
  BestScoreText_.setFillColor(sf::Color::Black);
  BestScoreText_.setCharacterSize(42);
  CurrentLevelText_.setFont(DigitFont_);
  CurrentLevelText_.setFillColor(sf::Color::Black);
  CurrentLevelText_.setCharacterSize(30);
}

void GameStates::upgrateLevel() noexcept {
  ShipMoveSpeed_ *= WeaponSpeedUpFactor_;
  BulletSpeed_ *= WeaponSpeedUpFactor_;

  AlienMoveSpeed_ *= AlienSpeedUpFactor_;

  ScorePerAlien_ *= upgrateLevelBonusFactor_;

  CurrentLevel_ += 1;
  updateCurrentLevelText_();
}

void GameStates::resetGameStates() {
  Hp_ = 3;
  Score_ = 0;
  CurrentLevel_ = 1;
  ShipMoveSpeed_ = static_settings::ShipMoveSpeed;
  BulletSpeed_ = static_settings::BulletSpeed;
  AlienMoveSpeed_ = static_settings::AlienMoveSpeed;
  ScorePerAlien_ = static_settings::ScorePerAlien;

  updateScoreText_();
  updateBestScoreText_();
  updateCurrentLevelText_();
}

void GameStates::dropHp() noexcept { Hp_ -= 1; }

void GameStates::killAlien() noexcept {
  Score_ += ScorePerAlien_;
  updateScoreText_();

  if (Score_ >= BestScore_) {
    BestScore_ = Score_;
    updateBestScoreText_();
  }
}

void GameStates::draw() {
  drawHp_();
  drawStatistics_();
}

void GameStates::updateScoreText_() {
  std::ostringstream OSS;
  OSS << "Score: " << Score_ << " ";
  ScoreText_.setString(OSS.str());
}

void GameStates::updateBestScoreText_() {
  std::ostringstream OSS;
  OSS << "BestScore: " << BestScore_ << " ";
  BestScoreText_.setString(OSS.str());
}

void GameStates::updateCurrentLevelText_() {
  std::ostringstream OSS;
  OSS << "Current Level: " << CurrentLevel_ << " ";
  CurrentLevelText_.setString(OSS.str());
}

void GameStates::drawHp_() {
  sf::Vector2f CurrentPos{0, 0};
  for (int i = 0; i < Hp_; i++) {
    ShipHpSprite_.setTopLeftTo(CurrentPos);
    Window_->draw(ShipHpSprite_.getSFSprite());
    CurrentPos.x += ShipHpImage_.getSize().x;
  }
}

void GameStates::drawStatistics_() {
  auto BestScoreWidth = BestScoreText_.getLocalBounds().width;
  BestScoreText_.setPosition(
      {static_settings::WindowMidTop.x - BestScoreWidth / 2, 0});
  Window_->draw(BestScoreText_);

  auto ScoreHeight = ScoreText_.getLocalBounds().height;
  auto ScoreWidth = ScoreText_.getLocalBounds().width;
  ScoreText_.setPosition({static_settings::WindowWidth - ScoreWidth, 0});
  Window_->draw(ScoreText_);

  auto CurrentLevelWidth = CurrentLevelText_.getLocalBounds().width;
  CurrentLevelText_.setPosition(
      {static_settings::WindowWidth - CurrentLevelWidth, ScoreHeight + 20});
  Window_->draw(CurrentLevelText_);
}