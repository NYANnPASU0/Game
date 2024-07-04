#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace sf;

class Coin
{
private:
	RectangleShape body;
public:
	Coin(Texture* texture, Vector2f size);
	void draw(RenderWindow& win);
	~Coin();
	void set_pos(sf::Vector2f newPos);
};