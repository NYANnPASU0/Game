#include "Collision.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Collision::Collision(RectangleShape& body) : body(body) {}

Collision::~Collision() {}

bool Collision::check_collision(const Collision& other, Vector2f& direction, float push)
{
	Collision other_o = other;
	Vector2f other_pos = other_o.get_position_coll();
	Vector2f other_hs = other_o.get_half_size();
	Vector2f this_pos = get_position_coll();
	Vector2f this_hs = get_half_size();

	float deltaX = other_pos.x - this_pos.x;
	float deltaY = other_pos.y - this_pos.y;

	float inters_X = abs(deltaX) - (other_hs.x + this_hs.x);
	float inters_Y = abs(deltaY) - (other_hs.y + this_hs.y);

	if (inters_X < 0.0f && inters_Y < 0.0f) //if they collide with this obj so let us know
	{
		//takes what it returns being between 0 and 1 being clamping between 0 and 1
		push = std::min(std::max(push, 0.0f), 1.0f);

		if ((inters_X) > (inters_Y)) {
			if (deltaX > 0.0f) {
				Move(inters_X * (1.0f - push), 0.0f);
				other_o.Move(-inters_X * push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-inters_X * (1.0f - push), 0.0f);
				other_o.Move(inters_X * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.0f) {
				Move(0.0f, inters_Y * (1.0f - push));
				other_o.Move(0.0f, -inters_Y * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				Move(0.0f, -inters_Y * (1.0f - push));
				other_o.Move(0.0f, inters_Y * push);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}
