#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#define Tile_Size 50
#define COLS 7
#define ROWS 7
#define seperation 15
#define No_Of_Tiles 6
#define tile_Sepration 65

sf::Vector2i ftile(372, 79);
int No_Of_Sides[No_Of_Tiles] = { 3,4,5,6,8,50 };
sf::Color Colors[No_Of_Tiles] = { sf::Color(0, 35, 51),sf::Color(25,51,0), sf::Color(51,0,0),sf::Color(91,28,104),sf::Color(229,255,204),sf::Color(70,150,255) };

void swap(int& x, int& y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;

}

void scoreBoard(sf::RenderWindow& window, sf::Font font)
{
    sf::Text target;
    target.setFont(font);
    target.setString("T A R G E T \n 2000");
    target.setCharacterSize(60);
    target.setFillColor(sf::Color(10, 35, 51));
    target.setOutlineColor(sf::Color::Black);
    target.setOutlineThickness(10);
    target.setPosition(window.getSize().x * 0.06, window.getSize().y * 0.1);


    sf::Text text;
    text.setFont(font);
    text.setString("S C O R E \n 0");
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 35, 51));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(10);
    text.setPosition(window.getSize().x * 0.06, window.getSize().y * 0.4);
    window.draw(text);
    window.draw(target);
}

void printTiles(sf::RenderWindow& window, sf::Color& color, int sides, int tileSize, float positionx, float positiony) {

    //Tile Highlight
    sf::RectangleShape tileHighlight;
    tileHighlight.setSize(sf::Vector2f(tile_Sepration, tile_Sepration));
    tileHighlight.setFillColor(sf::Color(128, 128, 128, 160));
    tileHighlight.setPosition(sf::Vector2f(positionx - seperation + 8, positiony - seperation + 8));

    sf::CircleShape tiles;
    tiles.setPointCount(sides);
    tiles.setRadius(tileSize / 2);
    tiles.setFillColor(color);
    tiles.setOutlineColor(sf::Color::Black);
    tiles.setOutlineThickness(4);
    tiles.setPosition(sf::Vector2f(positionx, positiony));
    window.draw(tiles);

    if (tiles.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) 
        window.draw(tileHighlight);
        
}

int main()
{
    srand(time(0));

    int positioning[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            positioning[i][j] = rand() % 6;
        }
    }

    sf::RenderWindow window(sf::VideoMode(960, 600), "CANDY CRUSH", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("background.jpg");
    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile("font.ttf");

    //tile background
    sf::RectangleShape tileBackground(sf::Vector2f(COLS * (Tile_Size + seperation) + seperation, ROWS * (Tile_Size + seperation) + seperation));
    tileBackground.setFillColor(sf::Color(33, 64, 95, 160));
    tileBackground.setOutlineThickness(8);
    tileBackground.setOutlineColor(sf::Color::Black);
    tileBackground.setPosition(window.getSize().x * 0.4 - seperation, window.getSize().y * 0.13);

    float positionx[COLS];
    float positiony[ROWS];
    for (int i = 0.0; i < COLS; i++)
        positionx[i] = (window.getSize().x * 2 / 5) + (tile_Sepration * i);

    for (int i = 0; i < ROWS; i++)
        positiony[i] = (window.getSize().y * 3 / 20) + (tile_Sepration * i);

    int click = 0;
    sf::Vector2i mouse;
    int x0 = 0, x2 = 0, y0 = 0, y2 = 0;
    int jpos=0, ipos=0;

    while (window.isOpen())
    {
        
        sf::Event evn;
        while (window.pollEvent(evn))
        {
            switch (evn.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (evn.key.code == sf::Keyboard::Escape)
                    window.close();
                break;

            }
            if (evn.type == sf::Event::MouseButtonPressed) {
                if (evn.key.code == sf::Mouse::Left)
                {
                    click++;
                    mouse = sf::Mouse::getPosition(window) - ftile;
                    std::cout << mouse.x << "  " << mouse.y;
                }
            }

        }

        if (click == 1)
        {
            x0 = mouse.x / Tile_Size;

            y0 = mouse.y / Tile_Size;
            std::cout << x0 << "  " << y0;
        }
        if (click == 2)
        {
            x2 = mouse.x / Tile_Size;

            y2 = mouse.y / Tile_Size;
            std::cout << x2 << "  " << y2;
            if (x2 - x0 == 1 || y2 - y0 == 1)
                swap(positioning[x0][y0], positioning[x2][y2]);
            
            else
                click = 1;
        }

        window.clear();
        window.draw(sprite);
        scoreBoard(window, font);
        window.draw(tileBackground);

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printTiles(window, Colors[positioning[i][j]], No_Of_Sides[positioning[i][j]], Tile_Size, positionx[j], positiony[i]);
            }
        }

        window.display();
    }

    return 0;
}