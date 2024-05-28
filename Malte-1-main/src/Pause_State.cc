#include "../includes/Pause_State.h"

#include <string>
#include <stdexcept>

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
Pause_State :: Pause_State ()
        :resume { false }, exit_menu { false }
{
    std::string file = "resources/fonts/Pixel_NES.otf"; 
    if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");
    resume_text = sf::Text{ "Resume Game", font, 48 };
    resume_text.setFillColor(sf::Color::Red);
    quit_menu_text = sf::Text{ "Quit To menu", font, 48 };

    if( !texture.loadFromFile("resources/images/Menu_Background.jpg"))
        throw std::invalid_argument ("Unable to load image");
    background = sf::Sprite(texture);

    menu_vector.push_back(resume_text);
    menu_vector.push_back(quit_menu_text);
}

/*
 * check for the 'enter' key.
 *
 * If it has been pressed we want to change to a new state.
 */

sf::Text& Pause_State :: get_text()
{   
    if(menu_selection == 0)
        return resume_text;
    else
        return quit_menu_text;
}

void Pause_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Enter )
        {
            if(menu_selection == 0)
                resume = true;
            else
                exit_menu = true;
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


void Pause_State :: update ()
{

}

void Pause_State :: render (RenderTarget & target)
{
    auto bounds { resume_text.getGlobalBounds () };
    auto size   { target.getSize () };

    resume_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 4);

    target.draw (resume_text);

    quit_menu_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) * 0.75);

    target.draw (quit_menu_text);
}

/*
 * If return has been pressed we change to the GAME_STATE, otherwise
 * we stay in MENU_STATE
 */
int Pause_State :: get_next_state()
{
    if (resume)
    {
        resume = false;
        return GAME_STATE;
    }
    else if(exit_menu)
    {
        exit_menu = false;
        return MENU_STATE;
    }
    else
    {
        return PAUSE_STATE;
    }
}