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

//pos - position

class Ground
{
private:
	RectangleShape body;
public:
	Ground(Texture* texture, Vector2f size, Vector2f pos);
	void draw(RenderWindow& win);
	Collision get_collider();
	~Ground();
};