#include "Coins.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Coin::Coin(Texture* texture, Vector2f size)
{
	body.setSize(size);
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
}

void Coin::draw(RenderWindow& win) { win.draw(body); }

Coin::~Coin(){ }

void Coin::set_pos(sf::Vector2f newPos) { body.setPosition(newPos); }
