#pragma once
#include "Animation.h"
#include "Collision.h"
#include "Coin.h"
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

class Player
{
private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool face_right;
	Vector2f velocity;
	float jump_height;
	SoundBuffer jump_buffer;
	Sound jump_sound;

public:
	Player(Texture* texture, Vector2u image_count, float switch_time, float speed, float jump_height);
	~Player();
	void update(float delta_time);
	void Draw(RenderWindow& win);
	void on_collision(Vector2f direction);
	bool is_idle = true;
	bool can_jump;
	int game_over = 0;
	Vector2f get_pos()
	{
		return body.getPosition();
	}
	Collision GetCollider()
	{
		return Collision(body);
	}

	bool isCollidingWithCoin(Coin* body)
	{
		if (Player::body.getGlobalBounds().intersects(body->get_global_bounds())) return true;
		return false;
	}
	void setPos(sf::Vector2f new_pos)
	{
		body.setPosition(new_pos);
	}
};