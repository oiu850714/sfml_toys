#include "space-invaders.hpp"
#include "settings.hpp"
#include <iostream>

SpaceInvaders::SpaceInvaders()
    : Window_(sf::VideoMode(1920, 1080), "Space Invaders"), Ship_(&Window_),
      Bullets_(&Window_, Ship_), Aliens_(&Window_)
{
}

SpaceInvaders::~SpaceInvaders() = default;

bool SpaceInvaders::isDone()
{
  return Done_;
}

void SpaceInvaders::handleInput()
{
  sf::Event event;
  while (Window_.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      quitGame_();
    }
    if (event.type == sf::Event::KeyPressed)
    {
      this->notify_(event);
      Ship_.notify(event);
      Bullets_.notify(event);
    }
    if (event.type == sf::Event::KeyReleased)
    {
      Ship_.notify(event);
    }
  }
}

void SpaceInvaders::notify_(const sf::Event &event)
{
  assert(event.type == sf::Event::KeyPressed);
  if (event.key.code == sf::Keyboard::Q)
  {
    quitGame_();
  }
}

void SpaceInvaders::quitGame_()
{
  Done_ = true;
  Window_.close();
}

void SpaceInvaders::update()
{
  // 60fps
  if (Clock_.getElapsedTime().asMilliseconds() <= 16.6)
  {
    return;
  }
  Clock_.restart();

  Ship_.update();
  Bullets_.update();
  Aliens_.update();
}

void SpaceInvaders::render()
{
  Window_.clear(settings::BackgroundColor);
  Ship_.draw();
  Bullets_.draw();
  Aliens_.draw();
  Window_.display();
}