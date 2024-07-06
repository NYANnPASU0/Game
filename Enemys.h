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
#include "Animation.h"

using namespace sf;

class Enemy
{

private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool face_right;
	Vector2f velocity;

public:
	Enemy(Texture* texture, Vector2f size, Vector2u image_count, float switch_time, float speed);
	~Enemy();
	void update(float delta_time);
	void Draw(RenderWindow& win);
	Collision get_collider()
	{
		return Collision(body);
	}
	void on_collision(Vector2f direction);
	FloatRect get_global_bounds()
	{
		return body.getGlobalBounds();
	}
	void set_position(sf::Vector2f new_pos)
	{
		body.setPosition(new_pos);
	}
	Vector2f get_pos()
	{
		return body.getPosition();
	}
};