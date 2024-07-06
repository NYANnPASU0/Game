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

using namespace sf;

class Collision
{

private:
	RectangleShape& body;
public:
	Collision(RectangleShape& body);
	~Collision();
	bool check_collision(const Collision& other, Vector2f& direction, float push);
	void Move(float dx, float dy)
	{
		body.move(dx, dy);
	}
	Vector2f get_position_coll()
	{
		return body.getPosition();
	}
	Vector2f get_half_size()
	{
		return body.getSize() / 2.0f;
	}
};