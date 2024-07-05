#include "PLayer.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Player::Player(Texture* texture, Vector2u image_count, float switch_time, float speed, float jump_height)
	: animation(texture, image_count, switch_time) {
		this->speed = speed;
		this->jump_height = jump_height;
		row = 0;
		faceRight = true;
		body.setSize(Vector2f(100.0f, 150.0f));
		body.setPosition(50.0f, 600.0f);
		body.setTexture(texture);
		body.setOrigin(body.getSize() / 2.0f);
}

void Player::Update(float delta_time)
{
	//velocity.x *= 0.00f; //slowly stop moving higher is slower time to stop
	if (Keyboard::isKeyPressed(Keyboard::A)) //left
		velocity.x -= speed;
	if (Keyboard::isKeyPressed(Keyboard::D)) //right
		velocity.x += speed;
	if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump)
	{
		if (game_over == 1) PlaySound(TEXT("Undertale-Undertale-game-over.wav"), NULL, SND_FILENAME | SND_ASYNC);
		can_jump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jump_height); //
	}
	velocity.y += 981.0f * delta_time;
	if (velocity.x == 0.0f)    row = 0; //doing idle animation
	else
	{
		row = 1; //movement animation
		if (velocity.x > 0.0f) faceRight = true;
		else faceRight = false;
	}
	if (can_jump == false) row = 2;
	animation.Update(row, delta_time, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * delta_time);
}

void Player::Draw(RenderWindow& win) { win.draw(body); }

void Player::On_collision(Vector2f direction)
{
	if (direction.x < 0.0f) { velocity.x = 0.0f; } //collision of left
	else if (direction.x > 0.0f) { velocity.x = 0.0f; } //collision of right
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;//collision of ground
		can_jump = true; //if colliding with ground you can jump
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

Vector2f Player::Getter_pos() { return body.getPosition(); }

Collision Player::Get_collider() { return Collision(body); }

bool Player::Colliding_with_coin(Coin* body)
{
	if (Player::body.getGlobalBounds().intersects(body->get_globalbounds())) return true;
	return false;
}

void Player::Set_pos(sf::Vector2f new_pos) { body.setPosition(new_pos); }

Player::~Player() {}
