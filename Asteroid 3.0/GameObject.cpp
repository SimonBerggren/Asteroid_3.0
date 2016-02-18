#include "GameObject.h"

GameObject::GameObject(const sf::Texture &texture, const sf::Vector2f & position)
{
	setTexture(texture);
	setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
	setPosition(position);
}

GameObject::~GameObject()
{

}

void GameObject::Update(float delta)
{
	move(m_Direction * m_Speed);

	if (RightSide() < 0.0f)									// out of bounds left side
		SetX(RightEntry());
	else if (LeftSide() > WINDOW_WIDTH)			// out of bounds right side
		SetX(LeftEntry());

	if (BottomSide() < 0.0f)								// out of bounds top side
		SetY(BottomEntry());
	else if (TopSide() > WINDOW_HEIGHT)		// out of bounds bottom side
		SetY(TopEntry());
}

void GameObject::Draw()
{
	window->draw(*this);
}