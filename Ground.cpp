#include "Ground.h"
#include <SFML/Graphics.hpp>

Ground::Ground(Texture* texture, Vector2f size, Vector2f pos)
{
	body.setSize(size); 
	body.setPosition(pos);
	body.setTexture(texture);
	body.setOrigin(size / 2.0f); //центр
}

void Ground::draw(RenderWindow& win) { win.draw(body); }

Ground::~Ground() { }
