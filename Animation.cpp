#include "Animation.h"
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

Animation::Animation(Texture* texture, Vector2u image_count, float switch_time)
{
	this->image_count = image_count;
	this->switch_time = switch_time;
	total_time = 0.0f;
	curr_image.x = 0;
	uvRect.width = texture->getSize().x / float(image_count.x);
	uvRect.height = texture->getSize().y / float(image_count.y);
}

Animation::~Animation() {}

void Animation::update(int row, float delta_time, bool face_right)
{
	curr_image.y = row;
	total_time += delta_time;
	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		curr_image.x++;
		if (curr_image.x >= image_count.x) curr_image.x = 0;
	}
	uvRect.top = curr_image.y * uvRect.height;
	if (face_right) 
	{
		uvRect.left = curr_image.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (curr_image.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
