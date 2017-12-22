#ifndef DOODLE_JUMP_CONSTS_H
#define DOODLE_JUMP_CONSTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <memory>

/// Window params
static const unsigned WINDOW_WIDTH = 400;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Doodle Jump";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const std::string ICON_PATH = "./resources/icon.png";
static const sf::Vector2u ICON_SIZE = {32, 32};

/// Game params
static const float G = 9.8f;
static const float TIME_ACCELERATOR = 7.5f;
static const float MOVE_SPEED = 500.f;
static const size_t PLATFORM_COUNT = 30;
static const unsigned MAX_PRECISION_COUNT = 128;

enum class Types : size_t
{
    Platform = 0,
    Doodler
};

#endif //DOODLE_JUMP_CONSTS_H
