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
#include "Animation.h"
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
	bool faceRight;
	Vector2f velocity;
	float jump_height;

public:

	bool is_idle = true; //he isn't moving and can run the animation of an idle position 
	bool can_jump;
	int game_over = 0;

	Player(Texture* texture, Vector2u image_count, float switch_time, float speed, float jump_height);
	void Update(float delta_time);
	void Draw(RenderWindow& win);
	void On_collision(Vector2f direction);
	Vector2f Getter_pos();
	Collision Get_collider();
	bool Colliding_with_coin(Coin* body);
	void Set_pos(sf::Vector2f new_pos);
	~Player();
};
