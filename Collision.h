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
#include <Windows.h>
#include <MMSystem.h>

using namespace sf;

class Collision
{
private:
	RectangleShape& body;

public:
	Collision(RectangleShape& body);
	bool check_collision(Collision& other, Vector2f& direction, float push); //wall is 0, a light object would be 1
	void move(float dx, float dy);
	Vector2f get_position_coll();
	Vector2f get_half_size();
	~Collision();
};