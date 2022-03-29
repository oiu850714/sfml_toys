#include <algorithm>

#include "bullets.hpp"

#include <SFML/Graphics/Color.hpp>

Bullet::Bullet(sf::RenderWindow *Window, const sf::Vector2f &StartPos)
    : Window_(Window), BulletShape_(settings::BulletSize) {
  BulletShape_.setPosition(StartPos);
  BulletShape_.setFillColor(sf::Color::Black);
}

void Bullet::update() {
  auto CurrentPos_ = BulletShape_.getPosition();
  BulletShape_.setPosition(
      {CurrentPos_.x, CurrentPos_.y - settings::BulletSpeed});
}

void Bullet::draw() { Window_->draw(BulletShape_); }

sf::Vector2f Bullet::getPosition() const { return BulletShape_.getPosition(); }

void Bullets::notify(const sf::Event &e) {
  assert(e.type == sf::Event::KeyPressed);
  if (e.key.code == sf::Keyboard::Space &&
      BulletsInSpace_.size() < settings::MaximumBullet) {
    BulletsInSpace_.push_back(Bullet(Window_, Ship_.getShipMozzlePos()));
  }
}

void Bullets::update() {
  for (auto &bullet : BulletsInSpace_) {
    bullet.update();
  }
  removeOutOfBoundBullets_();
}

void Bullets::removeOutOfBoundBullets_() {
  BulletsInSpace_.erase(
      std::remove_if(BulletsInSpace_.begin(), BulletsInSpace_.end(),
                     [](auto &Bullet) { return Bullet.getPosition().y <= 0; }),
      BulletsInSpace_.end());
}

void Bullets::draw() {
  for (auto &bullet : BulletsInSpace_) {
    bullet.draw();
  }
}
