#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction)
	: GameObject(*textures::Projectile(), position)
{
	this->m_Direction = direction;
	m_Speed = 20.0f;
	setRotation(utils::vec::ToDegrees(direction));

	switch (utils::rnd::Int(0, 5))
	{
	case 0: 	setColor(sf::Color::Red);		break;
	case 1: 	setColor(sf::Color::Blue);		break;
	case 2:	setColor(sf::Color::Cyan);		break;
	case 3: 	setColor(sf::Color::Green);		break;
	case 4: 	setColor(sf::Color::Yellow);		break;
	case 5: 	setColor(sf::Color::Magenta);	break;
	}
}