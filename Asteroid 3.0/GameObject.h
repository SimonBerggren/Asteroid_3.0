#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Window.h"
#include "Utilities.h"
#include "Assets.h"

class GameObject : public sf::Sprite
{
protected:
	float m_Speed;						// how fast the object is moving
	sf::Vector2f m_Direction;		// in which direction the object is moving

public:
	GameObject(const sf::Texture& texture, const sf::Vector2f& position);	// constructor
	virtual ~GameObject();																		// destructor

	virtual void Update(float delta);															// moves object in direction with speed
	virtual void Draw();																			// draws object to render window

	void SetX(float x) { setPosition(x, getPosition().y); }		// set x position
	void SetY(float y) { setPosition(getPosition().x, y); }		// set y position

	float X() const { return getPosition().x; }		// x position
	float Y() const { return getPosition().y; }		// y position

	sf::FloatRect GetRect() const { return sf::FloatRect(getPosition().x - getOrigin().x, getPosition().y - getOrigin().y, getLocalBounds().width, getLocalBounds().height); }
	sf::Vector2f GetDirection() const { return m_Direction; }
	float GetSpeed() const { return m_Speed; }

private:
	// functions below are purely for convencience when reading update function
	// outer side of object
	float LeftSide() const { return getPosition().x - getOrigin().x; }
	float RightSide() const { return getPosition().x + getOrigin().x; }
	float TopSide() const { return getPosition().y - getOrigin().y; }
	float BottomSide() const { return getPosition().y + getOrigin().y; }

	// where to spawn object if teleporting to other side of window
	float LeftEntry() const { return  -getOrigin().x; }
	float RightEntry() const { return WINDOW_WIDTH + getOrigin().x; }
	float TopEntry() const { return -getOrigin().y; }
	float BottomEntry() const { return WINDOW_HEIGHT + getOrigin().y; }
};