#include <algorithm>

#include "bullets.hpp"

#include <SFML/Graphics/Color.hpp>

Bullet::Bullet(sf::RenderWindow *Window, const sf::Texture &BulletTexture,
               const sf::Vector2f &StartPos)
    : Window_(Window) {
  Sprite_.setSFSprite(sf::Sprite(BulletTexture));
  Sprite_.setScale(getScaledFactor());
  Sprite_.setCenterTo(StartPos);
}

void Bullet::update(float BulletSpeed) { Sprite_.moveUp(BulletSpeed); }

void Bullet::draw() { Window_->draw(Sprite_.getSFSprite()); }

sf::Vector2f Bullet::getPosition() const { return Sprite_.getTopMid(); }

Bullets::Bullets(sf::RenderWindow *Window, const Ship &Ship,
                 const GameStates &GameStates)
    : Window_(Window), Ship_(Ship), GameStates_(GameStates) {

  BulletImage_.loadFromFile(static_settings::BulletImagePath);
  BulletTexture_.loadFromImage(BulletImage_);
}

void Bullets::notify(const sf::Event &e) {
  assert(e.type == sf::Event::KeyPressed);
  if (e.key.code == sf::Keyboard::Space &&
      BulletsInSpace_.size() < static_settings::MaximumBullet) {
    BulletsInSpace_.push_back(
        Bullet(Window_, BulletTexture_, Ship_.getShipMozzlePos()));
  }
}

void Bullets::update() {
  for (auto &bullet : BulletsInSpace_) {
    bullet.update(GameStates_.getBulletSpeed());
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

void Bullets::clear() { BulletsInSpace_.clear(); }