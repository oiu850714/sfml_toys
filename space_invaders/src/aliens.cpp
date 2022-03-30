#include "aliens.hpp"
#include "detail.hpp"
#include "static_settings.hpp"

#include <algorithm>
#include <functional>
#include <vector>

static std::vector<sf::Vector2f> NewAliensCoordinates(sf::Vector2f AlienSize) {
  auto WindowSize = static_settings::WindowSize;
  std::vector<sf::Vector2f> Ret;
  auto RightBoundary = WindowSize.x - AlienSize.x;
  auto LowerBoundary = WindowSize.y - 3 * AlienSize.y;
  for (auto X = AlienSize.x; X <= RightBoundary; X += 2 * AlienSize.x) {
    for (auto Y = AlienSize.y; Y <= LowerBoundary; Y += 2 * AlienSize.y) {
      Ret.push_back(sf::Vector2f(X, Y));
    }
  }
  return Ret;
}

Alien::Alien(sf::RenderWindow *Window, const sf::Texture &AlienTexture,
             const sf::Vector2f &StartPos)
    : Window_(Window) {

  Sprite_.setSFSprite(sf::Sprite(AlienTexture));
  Sprite_.setScale(getScaledFactor());
  Sprite_.setCenterTo(StartPos);
}

void Alien::update(float AlienSpeed) {
  Sprite_.moveX(AlienSpeed * Aliens::getAlienMoveDirection());
}

void Alien::draw() { Window_->draw(Sprite_.getSFSprite()); }

bool Alien::isReachingBoundary() const {
  return Sprite_.getMidRight().x >= static_settings::WindowSize.x ||
         Sprite_.getMidLeft().x <= 0;
}

bool Alien::reachedTerritory() const {
  return Sprite_.getBottomMid().y >= static_settings::WindowSize.y;
}

void Alien::drop() { Sprite_.moveY(static_settings::AlienDropSpeed); }

bool Alien::isShooted(const sf::Vector2f &ShootPos) const {
  return isInSprite(ShootPos, Sprite_);
}

int Aliens::AlienMoveDirection_ = 1;

Aliens::Aliens(sf::RenderWindow *Window, const GameStates &GameStates)
    : Window_(Window), GameStates_(GameStates) {
  AlienImage_.loadFromFile(static_settings::AlienImagePath);
  AlienTexture_.loadFromImage(AlienImage_);
  createNewAliens();
}

void Aliens::createNewAliens() {
  RemainAliens_.clear();

  sf::Vector2f AlienSize;
  {
    auto TextureSize = AlienTexture_.getSize();
    AlienSize.x = TextureSize.x * Alien::getScaledFactor();
    AlienSize.y = TextureSize.y * Alien::getScaledFactor();
  }

  for (auto AlienPos : NewAliensCoordinates(AlienSize)) {
    RemainAliens_.emplace_back(Alien(Window_, AlienTexture_, AlienPos));
  }
}

void Aliens::update() {
  if (isAliensReachingBoundary_()) {
    AlienMoveDirection_ *= -1;
    dropAliens_();
  }
  for (auto &Alien : RemainAliens_) {
    Alien.update(GameStates_.getAlienMoveSpeed());
  }
}

bool Aliens::isAliensReachingBoundary_() const {
  return std::any_of(RemainAliens_.begin(), RemainAliens_.end(),
                     std::mem_fn(&Alien::isReachingBoundary));
}

void Aliens::dropAliens_() {
  for (auto &Alien : RemainAliens_) {
    Alien.drop();
  }
}

int Aliens::removeShootedAliens(const std::vector<Bullet> &BulletData) {
  auto OldNumAliens = RemainAliens_.size();
  RemainAliens_.erase(
      std::remove_if(RemainAliens_.begin(), RemainAliens_.end(),
                     [&BulletData](auto &Alien) {
                       for (const auto &Bullet : BulletData) {
                         if (Alien.isShooted(Bullet.getPosition())) {
                           return true;
                         }
                       }
                       return false;
                     }),
      RemainAliens_.end());
  return OldNumAliens - RemainAliens_.size();
}

bool Aliens::killedSpaceShip(const Ship &Ship) const {
  return std::any_of(RemainAliens_.begin(), RemainAliens_.end(),
                     [&Ship](const auto &Alien) {
                       return Ship.isCollided(Alien.getPosition());
                     });
}

bool Aliens::reachedTerritory() const {
  return std::any_of(RemainAliens_.begin(), RemainAliens_.end(),
                     std::mem_fn(&Alien::reachedTerritory));
}

void Aliens::draw() {
  for (auto &Alien : RemainAliens_) {
    Alien.draw();
  }
}