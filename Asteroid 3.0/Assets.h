#pragma once
#include "SFML/Graphics/Texture.hpp"

// loads textures when needed and only loads one copy (singleton pattern)
namespace textures
{
	// ship texture
	static sf::Texture* Ship()
	{
		static sf::Texture texture;
		texture.loadFromFile("../Assets/Images/Ship.png");
		return &texture;
	}

	// asteroid texture
	static sf::Texture* Asteroid()
	{
		static sf::Texture texture;
		texture.loadFromFile("../Assets/Images/Asteroid.png");
		return &texture;
	}

	// projectile texture
	static sf::Texture* Projectile()
	{
		static sf::Texture texture;
		texture.loadFromFile("../Assets/Images/Projectile.png");
		return &texture;
	}
}

namespace fonts
{
	// standard font
	static sf::Font* Standard()
	{
		static sf::Font font;
		font.loadFromFile("../Assets/Fonts/Font.otf");
		return &font;
	}
}