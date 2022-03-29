#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>

// Make position setting more readable.
class PygameSpriteFacade
{
public:
  PygameSpriteFacade() = default;
  void setSFSprite(sf::Sprite SFSprite)
  {
    SFSprite_ = std::move(SFSprite);
  }
  const sf::Sprite &getSFSprite() const { return SFSprite_; }
  void setRightTo(float x);
  void setLeftTo(float x);
  void setTopTo(float y);
  void setBottomTo(float y);
  void setTopLeftTo(const sf::Vector2f &);
  void setTopMidTo(const sf::Vector2f &);
  void setTopRightTo(const sf::Vector2f &);
  void setMidLeftTo(const sf::Vector2f &);
  void setCenterTo(const sf::Vector2f &);
  void setMidRightTo(const sf::Vector2f &);
  void setBottomMidTo(const sf::Vector2f &);
  void setBottomRightTo(const sf::Vector2f &);
  void setBottomLeftTo(const sf::Vector2f &);

  sf::Vector2f getTopLeft() const;
  sf::Vector2f getTopMid() const;
  sf::Vector2f getTopRight() const;
  sf::Vector2f getMidLeft() const;
  sf::Vector2f getCenter() const;
  sf::Vector2f getMidRight() const;
  sf::Vector2f getBottomMid() const;
  sf::Vector2f getBottomRight() const;
  sf::Vector2f getBottomLeft() const;

  void moveRight(sf::Int32 x)
  {
    moveX(x);
  }

  void moveLeft(sf::Int32 x)
  {
    moveX(-x);
  }

  void moveUp(sf::Int32 y)
  {
    moveY(-y);
  }

  void moveDown(sf::Int32 y)
  {
    moveY(y);
  }

  void moveX(sf::Int32 x);
  void moveY(sf::Int32 y);

  void setScale(float scale)
  {
    SFSprite_.setScale(scale, scale);
  }

private:
  sf::Sprite SFSprite_;
  sf::Vector2f getScaledTextureSize_() const;
};