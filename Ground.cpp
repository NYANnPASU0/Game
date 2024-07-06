#include "Ground.h"
#include <SFML/Graphics.hpp>

Ground::Ground(Texture* texture, Vector2f size, Vector2f pos)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(pos);
}

Ground::~Ground() {}

void Ground::Draw(RenderWindow& win)
{
	win.draw(body);
}
