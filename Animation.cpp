#include "Animation.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Animation::Animation(Texture* texture, Vector2u image_count, float switch_time)
{
	this->image_count = image_count;
	this->switch_time = switch_time;
	total_time = 0.0f;
	current_image.x = 0;
	uvRect.width = texture->getSize().x / float(image_count.x);
	uvRect.height = texture->getSize().y / float(image_count.y);
}

void Animation::Update(int row, float delta_time, bool face_right)
{
	current_image.y = row;
	total_time += delta_time;
	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		current_image.x++;
		if (current_image.x >= image_count.x) current_image.x = 0;
	}
	uvRect.top = current_image.y * uvRect.height;
	if (face_right)
	{
		uvRect.left = current_image.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (current_image.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}

Animation::~Animation() {}
