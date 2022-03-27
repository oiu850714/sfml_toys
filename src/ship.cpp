#pragma once

#include "ship.hpp"

Ship::Ship(sf::RenderWindow *Window) : Window_(Window)
{
  Image_.loadFromFile(settings::ShipImagePath);
  Texture_.loadFromImage(Image_);

  Sprite_.setSFSprite(sf::Sprite{Texture_});
  Sprite_.setScale(2);
  Sprite_.setBottomMidTo(settings::WindowMidBottom);
}

void Ship::notify(const sf::Event &e)
{
  assert(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);
  if (e.type == sf::Event::KeyPressed)
  {
    if (e.key.code == sf::Keyboard::Right)
    {
      if (State_ == ShipState::LR_Release) {
        State_ = ShipState::R;
        return;
      }
      if (State_ == ShipState::R) {
        return;
      }
      if (State_ == ShipState::L) {
        State_ = ShipState::BOTH_LR;
        return;
      }
    }
    if (e.key.code == sf::Keyboard::Left)
    {
      if (State_ == ShipState::LR_Release) {
        State_ = ShipState::L;
        return;
      }
      if (State_ == ShipState::L) {
        return;
      }
      if (State_ == ShipState::R) {
        State_ = ShipState::BOTH_LR;
        return;
      }
    }
  }
  if (e.type == sf::Event::KeyReleased)
  {
    if (e.key.code == sf::Keyboard::Right)
    {
      if (State_ == ShipState::BOTH_LR) {
        State_ = ShipState::L;
      }
      if (State_ == ShipState::R) {
        State_ = ShipState::LR_Release;
        return;
      }
    }
    if (e.key.code == sf::Keyboard::Left)
    {
      if (State_ == ShipState::BOTH_LR) {
        State_ = ShipState::R;
      }
      if (State_ == ShipState::L) {
        State_ = ShipState::LR_Release;
        return;
      }
    }
  }
}

void Ship::update() {
  // TODO: Check range out of bound.
  if (State_ == ShipState::BOTH_LR || State_ == ShipState::LR_Release) {
    return;
  }
  if (State_ == ShipState::R) {
    Sprite_.moveRight(settings::ShipMoveSpeed);
  }
  if (State_ == ShipState::L) {
    Sprite_.moveLeft(settings::ShipMoveSpeed);
  }
}

void Ship::draw()
{
  Window_->draw(Sprite_.getSFSprite());
}
