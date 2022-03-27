#include "aliens.hpp"
#include "settings.hpp"

#include <algorithm>
#include <vector>
#include <functional>

static std::vector<sf::Vector2f> NewAliensCoordinates(sf::Vector2f AlienSize)
{
  auto WindowSize = settings::WindowSize;
  std::vector<sf::Vector2f> Ret;
  auto RightBoundary = WindowSize.x - AlienSize.x;
  auto LowerBoundary = WindowSize.y - 3 * AlienSize.y;
  for (auto X = AlienSize.x; X <= RightBoundary; X += 2 * AlienSize.x)
  {
    for (auto Y = AlienSize.y; Y <= LowerBoundary; Y += 2 * AlienSize.y)
    {
      Ret.push_back(sf::Vector2f(X, Y));
    }
  }
  return Ret;
}

Alien::Alien(sf::RenderWindow *Window, const sf::Texture &AlienTexture,
             const sf::Vector2f &StartPos)
    : Window_(Window)
{

  Sprite_.setSFSprite(sf::Sprite(AlienTexture));
  Sprite_.setScale(getScaledFactor());
  Sprite_.setCenterTo(StartPos);
}

void Alien::update()
{
  auto OldPos = Sprite_.getCenter();
  OldPos.x += settings::AlienMoveSpeed * Aliens::getAlienMoveDirection();
  Sprite_.setCenterTo(OldPos);
}

void Alien::draw()
{
  Window_->draw(Sprite_.getSFSprite());
}

bool Alien::isReachingBoundary() const
{
  return Sprite_.getMidRight().x >= settings::WindowSize.x || Sprite_.getMidLeft().x <= 0;
}

void Alien::drop()
{
  auto OldPos = Sprite_.getCenter();
  OldPos.y += settings::AlienDrawSpeed;
  Sprite_.setCenterTo(OldPos);
}

int Aliens::AlienMoveDirection_ = 1;

Aliens::Aliens(sf::RenderWindow *Window)
    : Window_(Window)
{
  AlienImage_.loadFromFile(settings::AlienImagePath);
  AlienTexture_.loadFromImage(AlienImage_);
  sf::Vector2f AlienSize;
  {
    auto TextureSize = AlienTexture_.getSize();
    AlienSize.x = TextureSize.x * Alien::getScaledFactor();
    AlienSize.y = TextureSize.y * Alien::getScaledFactor();
  }

  for (auto AlienPos : NewAliensCoordinates(AlienSize))
  {
    RemainAliens_.emplace_back(Alien(Window_, AlienTexture_, AlienPos));
  }
}

void Aliens::update()
{
  if (isAliensReachingBoundary_())
  {
    AlienMoveDirection_ *= -1;
    dropAliens_();
  }
  for (auto &Alien : RemainAliens_)
  {
    Alien.update();
  }
}

bool Aliens::isAliensReachingBoundary_() const
{
  return std::any_of(RemainAliens_.begin(), RemainAliens_.end(), std::mem_fn(&Alien::isReachingBoundary));
}

void Aliens::dropAliens_()
{
  for (auto &Alien : RemainAliens_)
  {
    Alien.drop();
  }
}

void Aliens::draw()
{
  for (auto &Alien : RemainAliens_)
  {
    Alien.draw();
  }
}