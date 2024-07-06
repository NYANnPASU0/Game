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

void ResizeCamera(const RenderWindow& win, View& view) {
    float aspectRatio = float(win.getSize().x) / float(win.getSize().y);
    view.setSize(CAMERA_HEIGHT * aspectRatio, CAMERA_HEIGHT);
}

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
    win.setFramerateLimit(60);

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
    background_t.loadFromFile("assets/background.jpg");
    RectangleShape background1(Vector2f(12288, 728));
    background1.setTexture(&background_t);
    background1.setOrigin(700, 0);


    Texture playerTexture;
    playerTexture.loadFromFile("assets/sonic_square.png");
    Player player(&playerTexture, Vector2u(3, 3), 0.3f, 400.0f, 200.0f);


    Texture sonic;
    sonic.loadFromFile("assets/sonic_square.png");

    Texture sonic_lives;
    sonic_lives.loadFromFile("assets/sonic_live_сount.png");
    Sprite sprite_sonic_lives;
    sprite_sonic_lives.setTexture(sonic_lives);
    sprite_sonic_lives.setPosition(60, 610);

    Texture game_over;
    game_over.loadFromFile("assets/game_over_1_.png");

    Texture game_win;
    game_win.loadFromFile("assets/GoalSign.png");

    Texture ground_texture;
    ground_texture.loadFromFile("assets/groundTile.png");

    Texture wall_texture;
    wall_texture.loadFromFile("assets/WallSprite.png");

    Texture enemy_t;
    enemy_t.loadFromFile("assets/enemy.png");



    std::vector <Ground> groundTiles;
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(0.0f, 700.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(500.0f, 868.0f))); //wall
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(1090.0f, 640.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(1200.0f, 700.0f))); //wall
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(2200.0f,500.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(2700.0f, 735.0f))); //wall
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(3280.0f, 680.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(3100.0f, 600.0f))); //wall
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(3680.0f, 680.0f))); //ground
    //gulf
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(4950.0f, 680.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(5000.0f, 740.0f))); //wall
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(5570.0f, 502.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(6000.0f, 740.0f))); //wal
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(6580.0f, 680.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(6500.0f, 600.0f))); //wal
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(7050.0f,365.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(7550.0f, 600.0f))); //wal
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(7600.0f, 680.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(7900.0f, 600.0f))); //wal
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(8500.0f, 680.0f))); //ground
    //gulf
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(9800.0f,550.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(9900.0f, 235.0f))); //wal
    groundTiles.push_back(Ground(&ground_texture, Vector2f(1024.0f, 84.0f), Vector2f(11000.0f,450.0f))); //ground
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(10050.0f, 235.0f))); //wal
    groundTiles.push_back(Ground(&wall_texture, Vector2f(159.0f, 562.0f), Vector2f(10200.0f, 235.0f))); //wal 





    std::vector <Enemy*> enemy_vec;
    Enemy enemy1(Enemy(&enemy_t, Vector2f(123.0f, 90.0f), Vector2u(3, 1), 0.3f, 40.0f));
    Enemy enemy2(Enemy(&enemy_t, Vector2f(123.0f, 90.0f), Vector2u(3, 1), 0.3f, 40.0f));
    enemy1.set_position({900, 550});
    enemy2.set_position({460, 550});
    enemy_vec.push_back(&enemy1);
    enemy_vec.push_back(&enemy2);




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
    Coin coin9(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin10(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin11(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin12(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin13(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin14(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin15(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin16(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin17(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin18(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin19(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin20(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin21(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin22(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin23(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin24(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin25(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin26(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin27(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin28(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin29(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin30(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin31(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin32(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin33(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin34(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin35(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin36(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin37(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin38(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin39(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin40(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin41(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin42(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin43(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin44(Coin(&rings, Vector2f(50.0f, 50.0f)));
    Coin coin45(Coin(&rings, Vector2f(50.0f, 50.0f)));

    coin1.set_position({300, 600});
    coin2.set_position({900, 550});
    coin3.set_position({700, 550 });
    coin4.set_position({800, 550 });
    coin5.set_position({1450, 550 });
    coin6.set_position({1550, 550 });
    coin7.set_position({1850, 400 });
    coin8.set_position({1950, 400 });
    coin9.set_position({ 2050, 400 });
    coin10.set_position({ 2150, 400 });
    coin11.set_position({ 2250, 400 });
    coin12.set_position({ 2350, 400 });
    coin13.set_position({ 2450, 400 });
    coin14.set_position({ 2550, 400 });
    coin15.set_position({ 2650, 400 });
    coin16.set_position({ 2890, 600 });
    coin17.set_position({ 3050, 300 });
    coin18.set_position({ 3150, 300 });
    coin19.set_position({ 3350, 580 });
    coin20.set_position({ 3550, 580 });
    coin21.set_position({ 3750, 580 });
    coin22.set_position({ 3950, 580 });
    coin23.set_position({ 4330, 390 });
    coin24.set_position({ 4630, 580 });
    coin25.set_position({ 4780, 580 });
    coin26.set_position({ 5200, 400 });
    coin27.set_position({ 5400, 400 });
    coin28.set_position({ 5600, 400 });
    coin29.set_position({ 5800, 400 });
    coin30.set_position({ 6200, 580 });
    coin31.set_position({ 6350, 580 });
    coin32.set_position({ 6600, 290 });
    coin33.set_position({ 6800, 290 });
    coin34.set_position({ 7000, 290 });
    coin35.set_position({ 7200, 290 });
    coin36.set_position({ 7400, 290 });
    coin37.set_position({ 7900, 290 });
    coin38.set_position({ 8100, 600 });
    coin39.set_position({ 8300, 600 });
    coin40.set_position({ 8500, 600 });
    coin41.set_position({ 8700, 600 });
    coin42.set_position({ 8900, 600 });
    coin43.set_position({ 9100, 520 });
    coin44.set_position({ 9500, 480 });
    coin45.set_position({ 9600, 480 });

    rings_vect.push_back(&coin1);
    rings_vect.push_back(&coin2);
    rings_vect.push_back(&coin3);
    rings_vect.push_back(&coin4);
    rings_vect.push_back(&coin5);
    rings_vect.push_back(&coin6);
    rings_vect.push_back(&coin7);
    rings_vect.push_back(&coin8);
    rings_vect.push_back(&coin9);
    rings_vect.push_back(&coin10);
    rings_vect.push_back(&coin11);
    rings_vect.push_back(&coin12);
    rings_vect.push_back(&coin13);
    rings_vect.push_back(&coin14);
    rings_vect.push_back(&coin15);
    rings_vect.push_back(&coin16);
    rings_vect.push_back(&coin17);
    rings_vect.push_back(&coin18);
    rings_vect.push_back(&coin19);
    rings_vect.push_back(&coin20);
    rings_vect.push_back(&coin21);
    rings_vect.push_back(&coin22);
    rings_vect.push_back(&coin23);
    rings_vect.push_back(&coin24);
    rings_vect.push_back(&coin25);
    rings_vect.push_back(&coin26);
    rings_vect.push_back(&coin27);
    rings_vect.push_back(&coin28);
    rings_vect.push_back(&coin29);
    rings_vect.push_back(&coin30);
    rings_vect.push_back(&coin31);
    rings_vect.push_back(&coin32);
    rings_vect.push_back(&coin33);
    rings_vect.push_back(&coin34);
    rings_vect.push_back(&coin35);
    rings_vect.push_back(&coin36);
    rings_vect.push_back(&coin37);
    rings_vect.push_back(&coin38);
    rings_vect.push_back(&coin39);
    rings_vect.push_back(&coin40);
    rings_vect.push_back(&coin41);
    rings_vect.push_back(&coin42);
    rings_vect.push_back(&coin43);
    rings_vect.push_back(&coin44);
    rings_vect.push_back(&coin45);
    SoundBuffer coin_buffer;
    Sound coin_sound;
    if (!coin_buffer.loadFromFile("themes!/collecting-coins.wav"))
    {
        std::cout << "Could not load coin collecting sound." << std::endl;
    }
    coin_sound.setBuffer(coin_buffer);


    SoundBuffer jump_biffer;
    Sound jump_sound;
    if (!jump_biffer.loadFromFile("themes!/jump.wav"))
    {
        std::cout << "Failed to load jump sound." << std::endl;
    }
    jump_sound.setBuffer(jump_biffer);

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
    bool volume_set = true;
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
                deltaTime = clock.restart().asSeconds();
                if (deltaTime > 1.0f / 20.0f)
                    deltaTime = 1.0f / 20.0f;
                player.update(deltaTime);
                if (event.type == Event::Resized)
                    ResizeCamera(win, view);
                if (green_hill_zone.getStatus() != Music::Playing)
                {
                    green_hill_zone.play();
                };
                green_hill_zone.setVolume(70);
                Vector2f direction;
                for (Ground& ground : groundTiles) {
                    if (ground.get_collider().check_collision(player.GetCollider(), direction, 1.0f)) {
                        player.on_collision(direction);
                    }
                }
                for (Coin* rings : rings_vect) {
                    if (rings->get_collider().check_collision(player.GetCollider(), direction, 1.0f)) {
                        player.on_collision(direction);
                        rings_count = rings_count + 1;
                        rings->set_position({
                            1000,
                            4002
                            }); //throws coin away
                        coin_sound.play();
                        coin_sound.setVolume(100);
                    }
                    ssRings.str("");
                    ssRings << "RINGS: " << rings_count;
                    text_rings_count.setString(ssRings.str());
                }

                for (Enemy* enemies : enemy_vec) {
                    enemies->update(deltaTime);

                    for (Ground& ground : groundTiles) {
                        if (ground.get_collider().check_collision(enemies->get_collider(), direction, 1.0f)) {
                            enemies->on_collision(direction);
                        }
                    }
                    if (enemies->get_collider().check_collision(player.GetCollider(), direction, 1.0f)) {
                        if (player.can_jump == false) {
                            player.on_collision(direction);
                            score = score + 100;
                            enemies->set_position({
                                1000,
                                4002
                                }); //throws enemy away
                        }
                        else {
                            player.on_collision(direction);
                            score = 0;
                            player.setPos({
                                0,
                                685
                                });
                            lives = lives - 1;
                        }
                    }
                    ssScore.str("");
                    ssScore << "SCORE: " << score;
                    text_score_board.setString(ssScore.str());
                    ssLives.str("");
                    ssLives << lives;
                    text_live.setString(ssLives.str());
                }
                if (increSecs <= 60) {
                    increSecs++;
                }
                if (increSecs == 60) {
                    secs = secs + 1;
                    increSecs = 0;
                }
                if (secs == 60) {
                    mins = mins + 1;
                    secs = 0;
                }
                std::string m = std::to_string(mins);
                std::string s = std::to_string(secs);

                std::string timer = m + ":" + s;
                if (rings_count == 50) {
                    player.setPos({
                        -1000,
                        -3820
                        });

                }
                std::ostringstream ssTime;
                ssTime << "TIME: " << timer;
                Text time;
                time.setFont(font_for_all);
                time.setFillColor(Color::Yellow);
                time.setString(ssTime.str());
                time.setPosition(-125.0f, 650.0f);
                if (lives <= 0) {
                    player.game_over = 1;
                    player.setPos({
                        -100,
                        -382
                        }); //throws player away
                }
                win.setView(view);
                view.setCenter(player.get_pos());
                win.draw(background1);
                for (std::vector<Enemy*>::iterator it = enemy_vec.begin(); it != enemy_vec.end(); it++)
                {
                    (*it)->Draw(win);
                }
                for (std::vector<Coin*>::iterator it = rings_vect.begin(); it != rings_vect.end(); it++)
                {
                    (*it)->Draw(win);
                }
                for (std::vector<Ground>::iterator it = groundTiles.begin(); it != groundTiles.end(); it++)
                {
                    it->Draw(win);
                }
                player.Draw(win);
                win.draw(time);
                win.draw(text_score_board);
                win.draw(text_rings_count);
                win.draw(text_live);
                win.display();
            }
        }
    }
}