
#include "pomocne.hpp"
#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>



namespace pomocne
{
    using namespace std;

    void kolor(sf::RectangleShape& shape);

    constexpr int spanko{ 30 };
    constexpr float ruch{ 100.0 };

    void klawa(sf::RectangleShape& shape, int& licznik)
    {
        this_thread::sleep_for(chrono::milliseconds(spanko));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            shape.move(-0.1f * ruch, 0.0f);
            kolor(shape);
            licznik++;
            cout << licznik << endl;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            shape.move(0.1f * ruch, 0.0f);
            kolor(shape);
            licznik++;
            cout << licznik << endl;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            shape.move(0.0f, -0.1f * ruch);
            kolor(shape);
            licznik++;
            cout << licznik << endl;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            shape.move(0.0f, 0.1f * ruch);
            kolor(shape);
            licznik++;
            cout << licznik << endl;
        }
    }

    void mysz(sf::RenderWindow& window, sf::RectangleShape& shape, int& licznik)
    {
        this_thread::sleep_for(chrono::milliseconds(spanko));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            shape.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            kolor(shape);
            licznik++;
            cout << licznik;
            cout << " |X| " << static_cast<float>(mousePos.x) << " |Y| " << static_cast<float>(mousePos.y) << endl;
        }
    }

    void kolor(sf::RectangleShape& shape)
    {
        unsigned char r = rand() % 256;
        unsigned char g = rand() % 256;
        unsigned char b = rand() % 256;
        unsigned char a = rand() % 256;
        sf::Color nowyKolor(r, g, b, a);
        shape.setFillColor(nowyKolor);
    }

    void przemieszczanie()
    {
        sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
        sf::RectangleShape shape(sf::Vector2f(200.0f, 200.0f));
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(100.f, 100.f);
        int licznik{};

        while (window.isOpen())
        {
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    cout << "WIDTH : " << evnt.size.width << " HIGHT : " << evnt.size.height << endl;
                    break;
                case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128)
                    {
                        printf("%c", evnt.text.unicode);
                    }
                default:
                    break;
                }
            }
            klawa(shape, licznik);
            mysz(window, shape, licznik);

            window.clear();
            window.draw(shape);
            window.display();
        }
    }
}