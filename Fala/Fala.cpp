// Fala.cpp : Defines the entry point for the console application.
//

#pragma once

#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>

#include "pomocne.hpp"


using namespace std;

constexpr int spanko{ 30 };
constexpr float ruch{ 100.0 };

struct Wezel
{
    Wezel(int position);
    void drowMe(float period);
    sf::RectangleShape shape;
    float x{ 0 };
    float y{ 400.0 };
    float size{ 20.0 };
};

Wezel::Wezel(int position)
{
    shape = sf::RectangleShape(sf::Vector2f(10.0f, 10.0f));
    shape.setFillColor(sf::Color::Red);
    x = static_cast<float>(position) * size + size/2;
    cout << " x = " << x << endl;
    shape.setOrigin(-x , -y);
}

void Wezel::drowMe(float period)
{
    float nY = y + 10.f * sin(x + period);
    shape.setOrigin(-x, -nY);
}

void changePositionOfWezel(vector<Wezel>& wezly, const float chaneg)
{
    int counter{ 0 };
    for (auto& w : wezly)
    {
        w.drowMe(chaneg);
        counter++;
    }
}

void drowWezly(sf::RenderWindow& window, vector<Wezel>& wezly)
{
    for (const auto& w : wezly)
    {
        cout << "*";
        window.draw(w.shape);
    }
    cout << endl;
}

void fala()
{
    const float amp{10.0};
    sf::RenderWindow window(sf::VideoMode(800, 800), "FALA", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.setFramerateLimit(30);
    vector<Wezel> wezly{};
    int counter{ 0 };

    int w{ 0 };
    cout << "ile wezlow\n";
    cin >> w;
    for (int i = 0; i <= w; i++)
    {
        wezly.push_back(Wezel(i));
    }

    while (window.isOpen() && counter < 200)
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

        cout << counter;
        window.clear();

        changePositionOfWezel(wezly, counter);
        drowWezly(window, wezly);
        window.display();
        counter++;
    }
    window.close();
}

struct Wezel2
{
    Wezel2(float size);
    void dupa(sf::RenderWindow& window);
    sf::RectangleShape shape;
};

Wezel2::Wezel2(float size) : shape{}
{
    shape.setSize(sf::Vector2f(100.0f, 100.0f));
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(-400.0f, -400.0f);
}

void Wezel2::dupa(sf::RenderWindow& window)
{
    window.draw(shape);
}

void spr()
{
    //fala();
    sf::RenderWindow window(sf::VideoMode(800, 800), "FALA", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.setFramerateLimit(2);

    Wezel test(3);
    Wezel2 test2(200.0f);
    sf::RectangleShape shape(sf::Vector2f(200.0f, 200.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(-400.0f, -400.0f);
    cout << "X : " << test.shape.getOrigin().x << " Y: " << test.shape.getOrigin().y << endl;

    long long counter{0};

    while (counter < 10)
    {
        counter++;
        window.clear();
        window.draw(shape);
        window.draw(test.shape);
        test2.dupa(window);
        cout << test.shape.getOrigin().x << " " << endl;
        window.display();
        cout << counter << endl;
    }
    cin >> counter;
    window.close();
}


int main()
{
    //spr();
    //pomocne::przemieszczanie();
    fala();

    return 0;
}