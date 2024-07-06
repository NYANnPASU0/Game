#include "Coin.h"

Coin::Coin(Texture* texture, Vector2f size)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
}

Coin::~Coin() {}

void Coin::Draw(RenderWindow& win)
{
	win.draw(body);
}
