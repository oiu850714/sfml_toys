#include "pygame-sprite-facade.hpp"

#include <SFML/Graphics/Texture.hpp>

void PygameSpriteFacade::setRightTo(float x) {
  setMidRightTo({x, getMidRight().y});
}

void PygameSpriteFacade::setLeftTo(float x) {
  setMidLeftTo({x, getMidLeft().y});
}

void PygameSpriteFacade::setTopTo(float y) { setTopMidTo({getTopMid().x, y}); }

void PygameSpriteFacade::setBottomTo(float y) {
  setBottomMidTo({getBottomMid().x, y});
}

void PygameSpriteFacade::setTopLeftTo(const sf::Vector2f &Pos) {
  SFSprite_.setPosition({Pos.x, Pos.y});
}

void PygameSpriteFacade::setTopMidTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, 0};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setTopRightTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x, 0};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setMidLeftTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{0, ScaledTextureSize.y / 2};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setCenterTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, ScaledTextureSize.y / 2};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setMidRightTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x, ScaledTextureSize.y / 2};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setBottomLeftTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{0, ScaledTextureSize.y};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setBottomMidTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, ScaledTextureSize.y};
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

void PygameSpriteFacade::setBottomRightTo(const sf::Vector2f &Pos) {
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset = ScaledTextureSize;
  SFSprite_.setPosition({Pos.x - Offset.x, Pos.y - Offset.y});
}

sf::Vector2f PygameSpriteFacade::getTopLeft() const {
  return SFSprite_.getPosition();
}

sf::Vector2f PygameSpriteFacade::getTopMid() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, 0};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getTopRight() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x, 0};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getMidLeft() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{0, ScaledTextureSize.y / 2};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getCenter() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, ScaledTextureSize.y / 2};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getMidRight() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x, ScaledTextureSize.y / 2};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getBottomLeft() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{0, ScaledTextureSize.y};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getBottomMid() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset{ScaledTextureSize.x / 2, ScaledTextureSize.y};
  return {Position.x + Offset.x, Position.y + Offset.y};
}

sf::Vector2f PygameSpriteFacade::getBottomRight() const {
  auto Position = SFSprite_.getPosition();
  auto ScaledTextureSize = getScaledTextureSize_();
  sf::Vector2f Offset = ScaledTextureSize;
  return {Position.x + Offset.x, Position.y + Offset.y};
}

void PygameSpriteFacade::moveX(sf::Int32 x) {
  auto OldPos = SFSprite_.getPosition();
  SFSprite_.setPosition({OldPos.x + x, OldPos.y});
}

void PygameSpriteFacade::moveY(sf::Int32 y) {
  auto OldPos = SFSprite_.getPosition();
  SFSprite_.setPosition({OldPos.x, OldPos.y + y});
}

sf::Vector2f PygameSpriteFacade::getScaledTextureSize_() const {
  auto TextureSize = SFSprite_.getTexture()->getSize();
  auto Scale = SFSprite_.getScale();
  return {TextureSize.x * Scale.x, TextureSize.y * Scale.y};
}