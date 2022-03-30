#pragma once

#include <SFML/Graphics.hpp>

namespace static_settings {
const sf::Color BackgroundColor{230, 230, 230};
const unsigned WindowWidth = 1920;
const unsigned WindowHeight = 1080;
const sf::Vector2u WindowSize{WindowWidth, WindowHeight};
const sf::Vector2f WindowMidBottom{WindowWidth / 2, WindowHeight};
const sf::Vector2f WindowMidTop{WindowWidth / 2, 0};

const std::string ShipImagePath = "assets/images/ship.bmp";
const std::string AlienImagePath = "assets/images/alien.bmp";
const std::string ArialFontPath = "assets/fonts/arial.ttf";

const int ShipMoveSpeed = 10;
const sf::Vector2f BulletSize{6, 30};
const int BulletSpeed = 30;
const int MaximumBullet = 5;

const int AlienMoveSpeed = 3;
const int AlienDropSpeed = 20;
const int ScorePerAlien = 100;
} // namespace static_settings
