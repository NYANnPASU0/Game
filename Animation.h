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

class Animation
{
private:
	Vector2u image_count;
	Vector2u curr_image;
	float total_time;
	float switch_time;

public:
	Animation(Texture* texture, Vector2u image_count, float switch_time);
	~Animation();
	void update(int row, float delta_time, bool face_right);
	IntRect uvRect;
};