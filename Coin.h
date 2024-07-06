#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include "Collision.h"
#include <string>
#include <sstream>
#include<list>
#include <Windows.h>
#include <MMSystem.h>

using namespace sf;

class Coin
{
private:
	RectangleShape body;

public:
	Coin(Texture* texture, Vector2f size);
	~Coin();
	void Draw(RenderWindow& win);
	Collision get_collider() {
		return Collision(body);
	}
	FloatRect get_global_bounds()
	{
		return body.getGlobalBounds();
	}
	void set_position(sf::Vector2f newPos)
	{
		body.setPosition(newPos);
	}
};
