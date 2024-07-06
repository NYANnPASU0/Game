#include "Player.h"
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

Player::Player(Texture* texture, Vector2u image_count, float switch_time, float speed, float jump_height) :
	animation(texture, image_count, switch_time)
{
	this->speed = speed;
	this->jump_height = jump_height;
	row = 0;
	face_right = true;
	body.setSize(Vector2f(100.0f, 150.0f));
	body.setPosition(50.0f, 600.0f);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
	if (!jump_buffer.loadFromFile("themes!/jump.wav")) std::cout << "FAIL";
	jump_sound.setBuffer(jump_buffer);
}

Player::~Player() {}

void Player::update(float delta_time)
{
	velocity.x *= 0.00f;
	if (Keyboard::isKeyPressed(Keyboard::A)) velocity.x -= speed;
	if (Keyboard::isKeyPressed(Keyboard::D)) velocity.x += speed;
	if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump)
	{
		/*if (game_over == 1) PlaySound(TEXT("Undertale-Undertale-game-over.wav"), NULL, SND_FILENAME | SND_ASYNC);*/
		can_jump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jump_height);
		jump_sound.play();
	}
	velocity.y += 981.0f * delta_time;
	if (velocity.x == 0.0f) row = 0;
	else
	{
		row = 1; //movement animation
		if (velocity.x > 0.0f) face_right = true; //face right
		else face_right = false; //face left
	}
	if (can_jump == false) row = 2;
	animation.update(row, delta_time, face_right);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * delta_time);
}

void Player::Draw(RenderWindow& win)
{
	win.draw(body);
}

void Player::on_collision(Vector2f direction)
{
	if (direction.x < 0.0f) velocity.x = 0.0f; //collision of left
	else if (direction.x > 0.0f) velocity.x = 0.0f; //collision of right
	if (direction.y < 0.0f)//collision of ground
	{
		velocity.y = 0.0f;
		can_jump = true; 
	}
	else if (direction.y > 0.0f) velocity.y = 0.0f; 
}
