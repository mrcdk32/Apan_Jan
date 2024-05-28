#include "../includes/End_State.h"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream> // testing

using namespace sf;

End_State :: End_State ()
        :go_to_menu {false}, read_from{"resources/Scores/highscores.txt"}, write_to {}, highscore {}
{
    read_from >> highscore;
    read_from.close();

    game_over_text.setFillColor(sf::Color::Red);
    game_over_text = sf::Text{ "Game Over", font, 48 };
    next_text.setFillColor(sf::Color::Red);
    next_text = sf::Text{ "Score:", font, 48 };
    high_score_text = sf::Text{ "Highscore:", font, 48};
}


void End_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if(event.key.code == Keyboard::Key::Escape || event.key.code == Keyboard::Key::Enter)
        go_to_menu = true;
    }
}

void End_State :: update ()
{
    read_from.open("resources/Scores/current_score.txt");
    read_from >> current_score;
    score = sf::Text{std::to_string(current_score), font, 48};
    read_from.close();

    read_from.open("resources/Scores/highscores.txt");
    read_from >> highscore;
    high_score = sf::Text{std::to_string(highscore), font, 48};
    read_from.close();

}

void End_State :: render (RenderTarget & target)
{
    auto bounds { game_over_text.getGlobalBounds () };
    auto size   { target.getSize () };

    game_over_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 4);

    target.draw (game_over_text);

    next_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 2);

    target.draw (next_text);

    score.setPosition ((size.x - bounds.width) * 1.25,
                      (size.y - bounds.height) / 2);

    target.draw (score);

    high_score_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 1.5);

    target.draw(high_score_text);

    high_score.setPosition ((size.x - bounds.width) / 1.35,
                      (size.y - bounds.height) / 1.25);
    
    target.draw (high_score);
}

/*
 * If return has been pressed we change to the GAME_STATE, otherwise
 * we stay in MENU_STATE
 */
int End_State :: get_next_state()
{
    if(go_to_menu)
    {
        read_from.open("resources/Scores/current_score.txt");
        read_from >> current_score;
        read_from.close();

        if(current_score > highscore)
        {
            write_to.open("resources/Scores/highscores.txt");
            write_to << current_score;
            write_to.close();
        }

        write_to.open("resources/Scores/current_score.txt");
        write_to.close();
        go_to_menu = false;
        return MENU_STATE;
    }
    else
    {
        return END_STATE;
    }
}