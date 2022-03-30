#pragma once

#include <algorithm>

#include "detail.hpp"
#include "ship.hpp"

Ship::Ship(sf::RenderWindow *Window, const GameStates &GameStates)
    : Window_(Window), GameStates_(GameStates) {
  Image_.loadFromFile(static_settings::ShipImagePath);
  Texture_.loadFromImage(Image_);

  Sprite_.setSFSprite(sf::Sprite{Texture_});
  Sprite_.setScale(2);
  Sprite_.setBottomMidTo(static_settings::WindowMidBottom);
}

void Ship::notify(const sf::Event &e) {
  assert(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);
  if (e.type == sf::Event::KeyPressed) {
    if (e.key.code == sf::Keyboard::Right) {
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
    if (e.key.code == sf::Keyboard::Left) {
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
  if (e.type == sf::Event::KeyReleased) {
    if (e.key.code == sf::Keyboard::Right) {
      if (State_ == ShipState::BOTH_LR) {
        State_ = ShipState::L;
      }
      if (State_ == ShipState::R) {
        State_ = ShipState::LR_Release;
        return;
      }
    }
    if (e.key.code == sf::Keyboard::Left) {
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

bool Ship::isCollided(const sf::Vector2f &Pos) const {
  return isInSprite(Pos, Sprite_);
}

void Ship::update() {
  if (State_ == ShipState::BOTH_LR || State_ == ShipState::LR_Release) {
    return;
  }
  if (State_ == ShipState::R) {
    auto MoveMent = std::min<float>(static_settings::WindowWidth -
                                        Sprite_.getBottomRight().x,
                                    GameStates_.getShipSpeed());
    Sprite_.moveRight(MoveMent);
  }
  if (State_ == ShipState::L) {
    auto MoveMent =
        std::min<float>(Sprite_.getBottomLeft().x, GameStates_.getShipSpeed());
    Sprite_.moveLeft(MoveMent);
  }
}

void Ship::draw() { Window_->draw(Sprite_.getSFSprite()); }

sf::Vector2f Ship::getShipMozzlePos() const { return Sprite_.getTopMid(); }

void Ship::reborn() {
  Sprite_.setBottomMidTo(static_settings::WindowMidBottom);
}