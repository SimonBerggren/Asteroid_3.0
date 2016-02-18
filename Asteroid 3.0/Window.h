#pragma once
#include "SFML\Graphics.hpp"

// we will only have one window at a time and most classes will need it
// title is here for consistency
#define WINDOW_TITLE "Asteroid 3.0 - by Simon Berggren"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

extern sf::RenderWindow* window;