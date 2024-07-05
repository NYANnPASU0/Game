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

class Animation
{
private:
	Vector2u image_count;
	Vector2u current_image;
	float total_time;
	float switch_time; //amount of time til next image

public:
	Animation(Texture* texture, Vector2u image_count, float switch_time);
	void Update(int row, float delta_time, bool face_right);
	IntRect uvRect; //defines the current visible area of ??the texture to display the animation
	~Animation();
};
