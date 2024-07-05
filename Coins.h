#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include<list>
#include "Ground.h"
#include "Coins.h"
#include "Collision.h"
#include <Windows.h>
#include <MMSystem.h>

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
	Collision get_collider();
	FloatRect get_globalbounds();
};