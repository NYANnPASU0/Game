#include "Collision.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Collision::Collision(RectangleShape& body) : body(body) {}

bool Collision::check_collision(Collision& other, Vector2f& direction, float push)
{
	Vector2f other_pos = other.get_position_coll();
	Vector2f other_half_size = other.get_half_size();
	Vector2f this_pos = get_position_coll();
	Vector2f this_half_size = get_half_size();

	float deltaX = other_pos.x - this_pos.x;
	float deltaY = other_pos.y - this_pos.y;

	float intersect_X = abs(deltaX) - (other_half_size.x + this_half_size.x);
	float intersect_Y = abs(deltaY) - (other_half_size.y + this_half_size.y);

	if (intersect_X < 0.0f && intersect_Y < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);
		if ((intersect_X) > (intersect_Y))
		{
			if (deltaX > 0.0f)
			{
				move(intersect_X * (1.0f - push), 0.0f);
				other.move(-intersect_X * push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				move(-intersect_X * (1.0f - push), 0.0f);
				other.move(intersect_X * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersect_Y * (1.0f - push));
				other.move(0.0f, -intersect_Y * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				move(0.0f, -intersect_Y * (1.0f - push));
				other.move(0.0f, intersect_Y * push);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}

void Collision::move(float dx, float dy) { body.move(dx, dy); }

Vector2f Collision::get_position_coll() { return body.getPosition(); }

Vector2f Collision::get_half_size() { return body.getSize() / 2.0f; }

Collision::~Collision() {}
