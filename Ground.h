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
#include <Windows.h>
#include <MMSystem.h>
#include "Collision.h"

using namespace sf;

class Ground
{
private:
	RectangleShape body;
public:
	Ground(Texture* texture, Vector2f size, Vector2f pos);
	~Ground();
	void Draw(RenderWindow& win);
	Collision get_collider()
	{
		return Collision(body);
	}
};