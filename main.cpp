#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    sf::RenderWindow win(sf::VideoMode(1280, 720), L"Poky");
    Image icon;
    if (!icon.loadFromFile("C:/Users/Лиза/Pictures/для игры/icon game.png")) {
        return 1;
    }
    win.setIcon(32,32, icon.getPixelsPtr());
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        win.clear();
        win.display();
    }

    return 0;
}