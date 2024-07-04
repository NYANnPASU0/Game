#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace sf;

Image icon, sonic_sprite;
Texture texture;
Sprite player;

RenderWindow win(VideoMode(960, 672), "Sonic the Hedgehog");
Event event;
Music main_menu;
bool settings_visible = false;

void open_image_while_exit() //функция для мема с соником при выходе их игры
{
    RenderWindow imageWindow(VideoMode(390, 125), "ERROR");
    Texture imageTexture;
    Sprite imageSprite;

    if (!imageTexture.loadFromFile("Image/sonic_hack.jpg")){ return; }

    imageSprite.setTexture(imageTexture);

    while (imageWindow.isOpen())
    {
        Event imageEvent;
        while (imageWindow.pollEvent(imageEvent))
        {
            if (imageEvent.type == Event::Closed)
                imageWindow.close();
        }

        imageWindow.clear();
        imageWindow.draw(imageSprite);
        imageWindow.display();
    }
}

void zone_checkpoint(RenderWindow& win, Music& main_menu, bool& settings_visible, Clock& clock) //чекпоинты(они врядли пригодятся)
{
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px.ttf"));

    Text checkpoint1;
    checkpoint1.setFont(type); // шрифт, загруженный ранее
    checkpoint1.setString(L"Green Hill Zone"); // текст
    checkpoint1.setCharacterSize(24); // размер шрифта
    checkpoint1.setFillColor(Color(25, 25, 112)); // цвет текста
    checkpoint1.setOutlineThickness(3); // Установка толщины обводки
    checkpoint1.setOutlineColor(Color::White);
    checkpoint1.setPosition(750, 200);


    Text checkpoint2;
    checkpoint2.setFont(type);
    checkpoint2.setString(L"Marble Zone");
    checkpoint2.setCharacterSize(24);
    checkpoint2.setFillColor(Color(25, 25, 112));
    checkpoint2.setOutlineThickness(3);
    checkpoint2.setOutlineColor(Color::White);
    checkpoint2.setPosition(750, 250);

    Text checkpoint3;
    checkpoint3.setFont(type);
    checkpoint3.setString(L"Spring Yard Zone"); 
    checkpoint3.setCharacterSize(24);
    checkpoint3.setFillColor(Color(25, 25, 112)); 
    checkpoint3.setOutlineThickness(3);
    checkpoint3.setOutlineColor(Color::White);
    checkpoint3.setPosition(750, 300);

    Text checkpoint4;
    checkpoint4.setFont(type); 
    checkpoint4.setString(L"Labyrinth Zone"); 
    checkpoint4.setCharacterSize(24); 
    checkpoint4.setFillColor(Color(25, 25, 112)); 
    checkpoint4.setOutlineThickness(3); 
    checkpoint4.setOutlineColor(Color::White);
    checkpoint4.setPosition(750, 350);

    Text checkpoint5;
    checkpoint5.setFont(type); 
    checkpoint5.setString(L"Star Light Zone"); 
    checkpoint5.setCharacterSize(24); 
    checkpoint5.setFillColor(Color(25, 25, 112)); 
    checkpoint5.setOutlineThickness(3); 
    checkpoint5.setOutlineColor(Color::White);
    checkpoint5.setPosition(750, 400);

    Text checkpoint6;
    checkpoint6.setFont(type); 
    checkpoint6.setString(L"Scrap Brain Zone"); 
    checkpoint6.setCharacterSize(24); 
    checkpoint6.setFillColor(Color(25, 25, 112)); 
    checkpoint6.setOutlineThickness(3); 
    checkpoint6.setOutlineColor(Color::White);
    checkpoint6.setPosition(750, 450);

    win.draw(checkpoint1);
    win.draw(checkpoint2);
    win.draw(checkpoint3);
    win.draw(checkpoint4);
    win.draw(checkpoint5);
    win.draw(checkpoint6);
}

bool rectangles_main_menu(RenderWindow& win, int& selectedMenuItem, Clock& clock, bool& GAME_START_MENU) //выбор меню
{
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px.ttf"));

    RectangleShape textmenuBlock1(Vector2f(200, 45)); // размеры прямоугольника
    textmenuBlock1.setFillColor(Color(255, 255, 224)); // цвет заливки
    textmenuBlock1.setOutlineThickness(2); // толщина границы
    textmenuBlock1.setOutlineColor(Color(255, 218, 185)); // цвет границы
    textmenuBlock1.setPosition(30, 200);
    Text text1;
    text1.setFont(type); // шрифт, загруженный ранее
    text1.setString(L"Start"); // текст
    text1.setCharacterSize(20); // размер шрифта
    text1.setFillColor(Color(250, 128, 114)); // цвет текста
    text1.setPosition(50, 210);

    RectangleShape textmenuBlock2(Vector2f(200, 45));
    textmenuBlock2.setFillColor(Color(255, 255, 224));
    textmenuBlock2.setOutlineThickness(2); 
    textmenuBlock2.setOutlineColor(Color(255, 218, 185));
    textmenuBlock2.setPosition(30, 280);
    Text text2;
    text2.setFont(type); 
    text2.setString(L"Checkpoints"); 
    text2.setCharacterSize(20); 
    text2.setFillColor(Color(250, 128, 114));
    text2.setPosition(50, 290);

    RectangleShape textmenuBlock3(Vector2f(200, 45));
    textmenuBlock3.setFillColor(Color(255, 255, 224)); 
    textmenuBlock3.setOutlineThickness(2);
    textmenuBlock3.setOutlineColor(Color(255, 218, 185));
    textmenuBlock3.setPosition(30, 360);
    Text text3;
    text3.setFont(type); 
    text3.setString(L"EXIT"); 
    text3.setCharacterSize(20); 
    text3.setFillColor(Color(250, 128, 114));
    text3.setPosition(50, 370);

    const Time timeInterval = milliseconds(200);

    // Проверяем, прошло ли достаточно времени с последнего нажатия
    if (event.type == Event::KeyPressed && clock.getElapsedTime() > timeInterval)
    {
        if (event.key.code == Keyboard::Up)
        {
            selectedMenuItem--;
            if (selectedMenuItem < 0)
                selectedMenuItem = 2; // Переход к последнему элементу
        }
        else if (event.key.code == Keyboard::Down)
        {
            selectedMenuItem++;
            if (selectedMenuItem > 2)
                selectedMenuItem = 0; // Переход к первому элементу
        }
        // Сбрасываем таймер после обработки нажатия
        clock.restart();
    }


    // Изменение цвета выбранного прямоугольника
    switch (selectedMenuItem)
    {
    case 0:
        textmenuBlock1.setFillColor(Color(32, 178, 170)); // цвет заливки
        text1.setFillColor(Color(224, 255, 255)); // цвет текста
        textmenuBlock1.setOutlineColor(Color(64, 224, 208)); // цвет границы
        if (event.key.code == Keyboard::Enter)
        {
            GAME_START_MENU = false;
            /*starting_game(win,main_menu,clock);*/
            return GAME_START_MENU;
        }
        settings_visible = false;
        break;
    case 1:
        textmenuBlock2.setFillColor(Color(32, 178, 170)); 
        text2.setFillColor(Color(224, 255, 255)); 
        textmenuBlock2.setOutlineColor(Color(64, 224, 208));
        if (event.key.code == Keyboard::Enter)
        {
            settings_visible = true;
            zone_checkpoint(win, main_menu, settings_visible, clock);
        }
        break;
    case 2:
        textmenuBlock3.setFillColor(Color(32, 178, 170)); 
        text3.setFillColor(Color(224, 255, 255)); 
        textmenuBlock3.setOutlineColor(Color(64, 224, 208)); 
        settings_visible = false;
        if (event.key.code == Keyboard::Enter) open_image_while_exit(); // Открываем новое окно с изображением
        break;
    }

    win.draw(textmenuBlock1);
    win.draw(textmenuBlock2);
    win.draw(textmenuBlock3);
    win.draw(text1);
    win.draw(text2);
    win.draw(text3);
}

int main()
{
    win.setMouseCursorVisible(false);

    if (!icon.loadFromFile("Image/images.jpg"))
    {
        return 1;
    }

    win.setIcon(32, 32, icon.getPixelsPtr());
    sonic_sprite.loadFromFile("Image/sonic.png");

    float width = 960;
    float height = 672;
    //фон экрана меню
    RectangleShape background(Vector2f(width, height));
    Texture wallpaper_menu;
    if (!wallpaper_menu.loadFromFile("Image/menu main (3).jpg")) return 4;
    background.setTexture(&wallpaper_menu);

    //музыка
    Music main_menu;//создаем объект музыки
    main_menu.openFromFile("themes!/Toby-Fox-Dating-Start_.ogg");
    main_menu.setVolume(50);
    main_menu.play();

    Music green_hill_zone;//создаем объект музыки
    green_hill_zone.openFromFile("themes!/Green-Hill-Zone-Act-1.ogg");
    green_hill_zone.setVolume(40);

    //шрифт для названия экрана
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px-Bold.ttf")) return 5;

    //текст с названием
    Text titul;
    titul.setFont(type); // шрифт
    titul.setString(L"Sonic the Hedgehog"); // текст
    titul.setCharacterSize(37); // размер шрифта
    titul.setFillColor(Color(46, 210, 255)); // цвет текста
    titul.setOutlineThickness(2);
    titul.setOutlineColor(Color(0, 92, 173));
    titul.setPosition(320, 50);

    static int selectedMenuItem = 0;
    Clock clock;
    bool GAME_START_MENU = true;








    while (win.isOpen())
    {
        while (win.pollEvent(event))
        {
            if (GAME_START_MENU)
            {

                win.clear();
                win.draw(background);
                win.draw(titul);
                rectangles_main_menu(win, selectedMenuItem, clock, GAME_START_MENU);
                win.display();
            }
            else
            {
                win.clear();
                main_menu.stop();
                if (green_hill_zone.getStatus() != Music::Playing)
                {
                    green_hill_zone.play();
                }
                win.display();
            }
        }
    }
    return 0;
}