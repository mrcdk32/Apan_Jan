#include "../includes/Menu_State.h"

#include <string>
#include <stdexcept>
#include <iostream> // testing

using namespace sf;

/*
 * Create the welcome message using the font given in
 * 'resources/fonts/font.ttf'.
 *
 * The first argument of the sf::Text constructor is what string
 * it should draw, the second argument is what font should be used
 * to draw the text and the final argument specifies the font-size
 * (in pixels) of the text.
 */
Menu_State :: Menu_State ()
        :play { false }, exit { false }, menu_selection {}
{
    start_text = sf::Text{ "Start Game", font, 48 };
    start_text.setFillColor(sf::Color::Red);
    quit_text = sf::Text{ "Quit Game", font, 48 };

    if( !texture.loadFromFile("resources/images/Menu_Background.png"))
        throw std::invalid_argument ("Unable to load image");
    background = sf::Sprite(texture);

    background.setScale(2.25, 2.25);
}

/*
 * check for the 'enter' key.
 *
 * If it has been pressed we want to change to a new state.
 */

sf::Text& Menu_State :: get_text()
{   
    if(menu_selection == 0)
        return start_text;
    else
        return quit_text;
}

void Menu_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Return )
        {
            if(menu_selection == 0)
                play = true;
            else
                exit = true;
        }

        if( event.key.code == Keyboard::Key::Down)
            {
                get_text().setFillColor(sf::Color::White);
                menu_selection = 1;
                get_text().setFillColor(sf::Color::Red);
            }

        if( event.key.code == Keyboard::Key::Up)
            {
                get_text().setFillColor(sf::Color::White);
                menu_selection = 0;
                get_text().setFillColor(sf::Color::Red);
            }
    }
}

void Menu_State :: update ()
{

}

void Menu_State :: render (RenderTarget & target)
{
    auto bounds { start_text.getGlobalBounds () };
    auto size   { target.getSize () };

    target.draw(background);

    start_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 4);

    target.draw (start_text);

    quit_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) * 0.75);

    target.draw (quit_text);

}

/*
 * If return has been pressed we change to the GAME_STATE, otherwise
 * we stay in MENU_STATE
 */
int Menu_State :: get_next_state()
{
    if (play)
    {
        play = false;
        return GAME_STATE;
    }
    else if(exit)
    {
        exit = false;
        return EXIT;
    }
    else
    {
        return MENU_STATE;
    }
}