#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include<list>
#include "Ground.h"
#include "Coins.h"
#include "Collision.h"
#include "Animation.h"
#include "PLayer.h"
#include <Windows.h>
#include <MMSystem.h>

using namespace sf;

Image icon, sonic_sprite;
Texture texture;
Sprite player;

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





    Texture sonic;
    sonic.loadFromFile("assets/sonic_square.png");
    Player player(&sonic, Vector2u(3, 3), 0.3f, 400.0f, 200.0f);

    Texture sonic_lives;
    sonic_lives.loadFromFile("assets/sonic_live_сount.png");

    Texture game_over;
    game_over.loadFromFile("assets/game_over_1_.png");

    Texture ground_texture;
    ground_texture.loadFromFile("assets/groundTile.png");

    Texture wall_texture;
    wall_texture.loadFromFile("assets/WallSprite.png");






    std::vector<Ground>Ground_Green_Hill_Zone;
    //_____________________________________________________________________________
    Font font_for_all;
    if (!font_for_all.loadFromFile("font/font_for_rings.ttf")) return 5;
    //_____________________________________________________________________________
    //rings--------------------------------------------------------------------------
    Texture rings;
    rings.loadFromFile("assets/ring.png");
    Coin coin1(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin2(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin3(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin4(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin5(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin6(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin7(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin8(Coin(&rings, Vector2f(50.0f, 50.0f)));


    std::vector<Coin*>Rings_Green_Hill_Zone;
    Rings_Green_Hill_Zone.push_back(&coin1);
    Rings_Green_Hill_Zone.push_back(&coin2);
    Rings_Green_Hill_Zone.push_back(&coin3);
    Rings_Green_Hill_Zone.push_back(&coin4);
    Rings_Green_Hill_Zone.push_back(&coin5);
    Rings_Green_Hill_Zone.push_back(&coin6);
    Rings_Green_Hill_Zone.push_back(&coin7);
    Rings_Green_Hill_Zone.push_back(&coin8);

    int rings_count = 0;

    Text text_Rings;
    text_Rings.setFont(font_for_all);
    text_Rings.setFillColor(Color::Yellow);
    text_Rings.setString("RINGS:");
    text_Rings.setPosition(40, 20);

    Text text_rings_count;
    text_rings_count.setFont(font_for_all);
    text_rings_count.setFillColor(Color::White); 
    std::ostringstream ssRings;
    ssRings << rings_count;
    text_rings_count.setString(ssRings.str());
    text_rings_count.setPosition(text_Rings.getGlobalBounds().width + text_Rings.getPosition().x + 30, 20);





    //time and speed ---------------------------------------------------
    int increSecs = 0;
    int secs = 0;
    int mins = 0;
    int score = 0;

    Text text_score;
    text_score.setFont(font_for_all);
    text_score.setFillColor(Color::Yellow);
    text_score.setString("SCORE:");
    text_score.setPosition(40, 60);

    Text text_score_board;
    text_score_board.setFont(font_for_all);
    text_score_board.setFillColor(Color::White);
    std::ostringstream ssScore;
    ssScore << score;
    text_score_board.setString(ssScore.str());
    text_score_board.setPosition(text_score.getGlobalBounds().width + text_score.getPosition().x + 30, 60);

    //lives--------------------------------------------------------------
    int lives = 3;
    Text text_live;
    std::ostringstream ssLives;
    ssLives << "LIVES:" << lives;
    text_live.setFont(font_for_all);
    text_live.setFillColor(Color::White);
    text_live.setString(ssLives.str());
    text_live.setPosition(40, 600);

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
                Vector2f direction; //direction into player on collision func
                for (int i = 0; i < Ground_Green_Hill_Zone.size(); i++) {
                    Ground& ground = Ground_Green_Hill_Zone[i];
                    if (ground.get_collider().check_collision(player.cet_collider(), direction, 1.0f)) {
                        player.OnCollision(direction);
                    }
                }

                win.draw(text_Rings);
                win.draw(text_rings_count);
                win.draw(text_score);
                win.draw(text_score_board);
                win.draw(text_live);
                win.display();
            }
        }
    }
    return 0;
}