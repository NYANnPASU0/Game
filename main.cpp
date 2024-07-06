#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include<list>
#include <Windows.h>
#include <MMSystem.h>
#include "Ground.h"
#include "Collision.h"
#include "Coin.h"
#include "Animation.h"
#include "Enemys.h"
#include "Player.h"

using namespace sf;

Image icon, sonic_sprite;
Texture texture;
static const float CAMERA_HEIGHT = 960.0f;

RenderWindow win(VideoMode(960, 672), "Sonic the Hedgehog");
Event event;
Music main_menu;
bool settings_visible = false;

void open_image_while_exit() //function for a sonic meme when their game comes out
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

void zone_checkpoint(RenderWindow& win, Music& main_menu, bool& settings_visible, Clock& clock) //checkpoints(they are unlikely to be useful)
{
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px.ttf"));

    Text checkpoint1;
    checkpoint1.setFont(type);
    checkpoint1.setString(L"Green Hill Zone");
    checkpoint1.setCharacterSize(24);
    checkpoint1.setFillColor(Color(25, 25, 112));
    checkpoint1.setOutlineThickness(3);
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

bool rectangles_main_menu(RenderWindow& win, int& selectedMenuItem, Clock& clock, bool& GAME_START_MENU) //menu selection
{
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px.ttf"));

    RectangleShape textmenuBlock1(Vector2f(200, 45)); // rectangle dimensions
    textmenuBlock1.setFillColor(Color(255, 255, 224)); // fill color
    textmenuBlock1.setOutlineThickness(2); // border thickness
    textmenuBlock1.setOutlineColor(Color(255, 218, 185)); // border color
    textmenuBlock1.setPosition(30, 200);
    Text text1;
    text1.setFont(type); // font downloaded previously
    text1.setString(L"Start"); // text
    text1.setCharacterSize(20); // font size
    text1.setFillColor(Color(250, 128, 114)); //text color
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

    // Checking whether enough time has passed since the last click
    if (event.type == Event::KeyPressed && clock.getElapsedTime() > timeInterval)
    {
        if (event.key.code == Keyboard::Up)
        {
            selectedMenuItem--;
            if (selectedMenuItem < 0)
                selectedMenuItem = 2; // Move to last element
        }
        else if (event.key.code == Keyboard::Down)
        {
            selectedMenuItem++;
            if (selectedMenuItem > 2)
                selectedMenuItem = 0; // Go to first element
        }
        // Reset the timer after processing the click
        clock.restart();
    }


    // Change the color of the selected rectangle
    switch (selectedMenuItem)
    {
    case 0:
        textmenuBlock1.setFillColor(Color(32, 178, 170)); //fill color
        text1.setFillColor(Color(224, 255, 255)); // text color
        textmenuBlock1.setOutlineColor(Color(64, 224, 208)); // border color
        if (event.key.code == Keyboard::Enter)
        {
            GAME_START_MENU = false;
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
    //menu screen background
    RectangleShape background(Vector2f(width, height));
    Texture wallpaper_menu;
    if (!wallpaper_menu.loadFromFile("Image/menu main (3).jpg")) return 4;
    background.setTexture(&wallpaper_menu);

    //misic
    Music main_menu;//создаем объект музыки
    main_menu.openFromFile("themes!/Toby-Fox-Dating-Start_.ogg");
    main_menu.setVolume(50);
    main_menu.play();

    Music green_hill_zone;//создаем объект музыки
    green_hill_zone.openFromFile("themes!/Green-Hill-Zone-Act-1.ogg");
    green_hill_zone.setVolume(40);

    //font for screen title
    Font type;
    if (!type.loadFromFile("font/Greybeard-11px-Bold.ttf")) return 5;

    //text with title
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
    float deltaTime = 0.0f;


    Texture background_t;
    background_t.loadFromFile("assets/background.png");
    RectangleShape background1(Vector2f(12288, 728));
    background1.setTexture(&background_t);
    background1.setOrigin(700, 0);



    Texture sonic;
    sonic.loadFromFile("assets/sonic_square.png");

    Texture sonic_lives;
    sonic_lives.loadFromFile("assets/sonic_live_сount.png");

    Texture game_over;
    game_over.loadFromFile("assets/game_over_1_.png");

    Texture game_win;
    game_win.loadFromFile("assets/win (1)(1).png");

    Texture ground_texture;
    ground_texture.loadFromFile("assets/groundTile.png");

    Texture wall_texture;
    wall_texture.loadFromFile("assets/WallSprite.png");

    Texture enemy_t;
    enemy_t.loadFromFile("assets/enemy.png");



    std::vector <Ground> groundTiles;
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(0.0f, 630.0f))); //ground
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(1180.0f, 630.0f))); //ground
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(1536.0f, 768.0f))); //ground
    //groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(2536.0f, 768.0f))); //ground
    //groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(-55.0f, 528.0f))); //wall at start of level
    //groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(1024.0f, 828.0f))); //wall2
    //groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(1424.0f, 728.0f))); //wall3
    //groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(1724.0f, 928.0f))); //wall4
    //groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(2100.0f, 528.0f))); 
    //groundTiles.push_back(Ground(&sonic_lives, Vector2f(96.0f, 32.0f), Vector2f(60.0f, 620.0f)));
    //groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(-100, -402))); 
    //groundTiles.push_back(Ground(&game_over, Vector2f(1024.0f, 728.0f), Vector2f(-100, -402))); //gamer over
    //groundTiles.push_back(Ground(&game_win, Vector2f(1024.0f, 728.0f), Vector2f(-1000, -3820))); //gamer won 




    Texture rings;
    rings.loadFromFile("assets/ring.png");
    std::vector <Coin*> rings_vect;
    Coin coin1(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin2(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin3(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin4(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin5(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin6(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin7(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin8(Coin(&rings, Vector2f(50.0f, 50.0f)));
    coin1.set_position({300, 550});
    coin2.set_position({900, 550});
    coin3.set_position({700, 550 });
    coin4.set_position({800, 550 });
    coin5.set_position({1200, 550 });
    coin6.set_position({1300, 550 });
    coin7.set_position({1850, 550 });
    coin8.set_position({1950, 550 });
    rings_vect.push_back(&coin1);
    rings_vect.push_back(&coin2);
    rings_vect.push_back(&coin3);
    rings_vect.push_back(&coin4);
    rings_vect.push_back(&coin5);
    rings_vect.push_back(&coin6);
    rings_vect.push_back(&coin7);
    rings_vect.push_back(&coin8);


    //_____________________________________________________________________________
    Font font_for_all;
    if (!font_for_all.loadFromFile("font/font_for_rings.ttf")) return 5;
    //_____________________________________________________________________________
    //rings--------------------------------------------------------------------------


    int rings_count = 0;

    Text text_rings_count;
    std::ostringstream ssRings;
    ssRings << "RINGS:" << rings_count;
    text_rings_count.setFont(font_for_all);
    text_rings_count.setFillColor(Color::Yellow);
    text_rings_count.setOutlineColor(Color(0, 0, 0));
    text_rings_count.setOutlineThickness(1);
    text_rings_count.setString(ssRings.str());
    text_rings_count.setPosition(40, 20);



    //time and speed ---------------------------------------------------
    int increSecs = 0;
    int secs = 0;
    int mins = 0;
    int score = 0;

    Text text_score_board;
    std::ostringstream ssScore;
    ssScore << "SCORE:" << score;
    text_score_board.setFont(font_for_all);
    text_score_board.setFillColor(Color::Yellow);
    text_score_board.setOutlineColor(Color(0, 0, 0));
    text_score_board.setOutlineThickness(1);
    text_score_board.setString(ssScore.str());
    text_score_board.setPosition(40, 60);

    //lives--------------------------------------------------------------
    int lives = 3;
    Text text_live;
    std::ostringstream ssLives;
    ssLives << lives;
    text_live.setFont(font_for_all);
    text_live.setFillColor(Color::White);
    text_live.setOutlineColor(Color(69, 69, 69));
    text_live.setOutlineThickness(1);
    text_live.setString(ssLives.str());
    text_live.setPosition(72, 610);

    View view(Vector2f(0.0f, 0.0f), Vector2f(CAMERA_HEIGHT, CAMERA_HEIGHT * 0.7));
    view.setCenter(Vector2f(width / 2, height / 2));

    while (win.isOpen())
    {
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed) win.close();
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
                win.setView(view);
                win.draw(background1);
                for (std::vector<Coin*>::iterator it = rings_vect.begin(); it != rings_vect.end(); ++it)
                {
                    (*it)->Draw(win);
                }
                for (std::vector<Ground>::iterator it = groundTiles.begin(); it != groundTiles.end(); ++it)
                {
                    it->Draw(win);
                }
                win.draw(text_score_board);
                win.draw(text_rings_count);
                win.draw(text_live);
                win.display();

            }
        }
    }
}