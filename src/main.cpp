// space_invaders.cpp : Defines the entry point for the application.
//

#include <SFML/Graphics.hpp>
#include <iostream>

#include "settings.hpp"
#include "ship.hpp"
#include "space-invaders.hpp"

using namespace std;

int main() {
  SpaceInvaders Game;
  while (!Game.isDone()) {
    Game.handleInput();
    Game.update();
    Game.render();
  }

  return 0;
}
