#include "space-invaders.hpp"
#include "static_settings.hpp"
#include <iostream>

#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

SpaceInvaders::SpaceInvaders()
    : Window_(sf::VideoMode(1920, 1080), "Space Invaders"),
      GameStates_(&Window_), Ship_(&Window_, GameStates_),
      Bullets_(&Window_, Ship_, GameStates_), Aliens_(&Window_, GameStates_) {}

SpaceInvaders::~SpaceInvaders() = default;

bool SpaceInvaders::isDone() { return Done_; }

void SpaceInvaders::handleInput() {
  sf::Event event;
  while (Window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      quitGame_();
    }
    if (event.type == sf::Event::KeyPressed) {
      this->notify_(event);
      Ship_.notify(event);
      Bullets_.notify(event);
    }
    if (event.type == sf::Event::KeyReleased) {
      Ship_.notify(event);
    }
  }
}

void SpaceInvaders::notify_(const sf::Event &event) {
  assert(event.type == sf::Event::KeyPressed);
  if (event.key.code == sf::Keyboard::Q) {
    quitGame_();
  }
}

void SpaceInvaders::quitGame_() {
  Done_ = true;
  Window_.close();
}

void SpaceInvaders::update() {
  // 60fps
  if (Clock_.getElapsedTime().asMilliseconds() <= 16.6) {
    return;
  }
  Clock_.restart();

  Ship_.update();
  Bullets_.update();
  Aliens_.update();

  checkCollisions_();
}

void SpaceInvaders::checkCollisions_() {
  if (Aliens_.killedSpaceShip(Ship_)) {
    resetBattleField_();
    GameStates_.dropHp();
    if (GameStates_.isDead()) {
      std::cout << "You Dead!\n";
      GameStates_.resetGameStates();
    }
  }
  for (int NumKilledAliens =
           Aliens_.removeShootedAliens(Bullets_.getBulletData());
       NumKilledAliens-- > 0;) {
    GameStates_.killAlien();
  }
  if (Aliens_.allBeenKilled()) {
    Aliens_.createNewAliens();
    GameStates_.upgrateLevel();
  }
}

void SpaceInvaders::resetBattleField_() {
  sf::sleep(sf::seconds(2));
  Ship_.reborn();
  Bullets_.clear();
  Aliens_.createNewAliens();
}

void SpaceInvaders::render() {
  Window_.clear(static_settings::BackgroundColor);
  Ship_.draw();
  Bullets_.draw();
  Aliens_.draw();
  GameStates_.draw();
  Window_.display();
}