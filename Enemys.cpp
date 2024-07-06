#include "Enemys.h"

Enemy::Enemy(Texture* texture, Vector2f size, Vector2u image_count, float switch_time, float speed) :
	animation(texture, image_count, switch_time) {
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	this->speed = speed;
	row = 0;
	face_right = true;
}

Enemy::~Enemy() {}

void Enemy::update(float delta_time)
{
	velocity.x = speed;
	velocity.y += 981.0f * delta_time;
	if (velocity.x >= 0.0f)
	{
		face_right = true; //face right
		row = 0;
	}
	else
	{
		face_right = false; //face left
		row = 0;
	}
	animation.update(row, delta_time, face_right);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * delta_time);
}

void Enemy::Draw(RenderWindow& win)
{
	win.draw(body);
}

void Enemy::on_collision(Vector2f direction)
{
	if (direction.x < 0.0f) speed = speed * -1; //collision of left
	else if (direction.x > 0.0f) speed = speed * -1; //collision of right
	if (direction.y < 0.0f) velocity.y = 0.0f; //collision of ground (bottom)
	else if (direction.y > 0.0f) velocity.y = 0.0f; //colliding on the top of sonics head
}
