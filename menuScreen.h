//
// Created by miami on 4/13/2018.
//

#ifndef DJJAM_MENUSCREEN_H
#define DJJAM_MENUSCREEN_H

#include <iostream>
#include "cScreen.h"

#include <SFML/Graphics.hpp>

class menuScreen : public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
public:
    menuScreen(void);
    virtual int Run(sf::RenderWindow &App);
};


menuScreen::menuScreen(void)
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
}

int menuScreen::Run(sf::RenderWindow &App)
{
    sf::Event Event;
    bool Running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    int alpha = 0;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/171016090659-trump-file-full-169.png"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    Sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("../cmake_modules/Images/OpenSans-Regular.ttf"))
    {
        std::cerr << "Error loading OpenSans-Regular.ttf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Play DJJAM");
    Menu1.setPosition({ 100, 150 });

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit Game");
    Menu2.setPosition({ 100, 200 });

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Continue");
    Menu3.setPosition({ 280.f, 160.f });

    if (playing)
    {
        alpha = alpha_max;
    }

    while (Running)
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        menu = 0;
                        break;
                    case sf::Keyboard::Down:
                        menu = 1;
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            //Let's get play !
                            playing = true;
                            return (1);
                        }
                        else
                        {
                            //Let's get work...
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        //When getting at alpha_max, we stop modifying the sprite
        if (alpha<alpha_max)
        {
            alpha++;
        }
        Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        if (menu == 0)
        {
            Menu1.setFillColor(sf::Color::Red);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::Black);
        }
        else
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::Red);
            Menu3.setFillColor(sf::Color::Black);
        }

        //Clearing screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        if (alpha == alpha_max)
        {
            if (playing)
            {
                App.draw(Menu3);
            }
            else
            {
                App.draw(Menu1);
            }
            App.draw(Menu2);
        }
        App.display();
    }
}

#endif //DJJAM_MENUSCREEN_H
