#include "../includes/Game_State.h"
#include "../includes/constants.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace sf;

Game_State :: Game_State ()
        :end_game { false } , pause {false}, highscore {}, delta_time {}, pause_time {}
{
    std::string file = "resources/fonts/Pixel_NES.otf"; 
    if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");
    Score_text = sf::Text{ "Score:", font, 38 };
    Life_text = sf::Text{ "Lives: ", font, 38 };
    
    Score_text.setFillColor(sf::Color::Blue);
    Life_text.setFillColor(sf::Color::Blue);
    Life.setFillColor(sf::Color::Blue);

    levels.push_back(new Level {1});
    levels.push_back(new Level {2});
    levels.push_back(new Level {3});
    current_level = levels.front();
    end_game = false;

    timer.restart();
}

Game_State :: ~Game_State ()
{
    current_level = nullptr;

    for(Level* lvl : levels)
    {
        delete lvl;
    }

    levels.clear();
}

void Game_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Escape )
            pause = true;

        if ( event.key.code == Keyboard::Key::T)
            end_game = true;
    }
}

void Game_State :: update ()
{  
    // Does not execute any code if the game has been paused.
   /*if(pause)
    {
        pause_time = timer.getElapsedTime().asSeconds();
        return;
    }*/

    if(pause)
    {
        delta_time += timer.restart().asSeconds();
        if(delta_time >= 0.1f)
        {
            timer.restart();
            pause = false;
        }
        return;
    }
        

    delta_time = timer.restart().asSeconds();
    //pause_time = 0;

    // Updates score and life
    read_current_score();
    Life = sf::Text{ std::to_string(current_level->get_player().get_life()), font, 38};
    Score = sf::Text{std::to_string(highscore), font, 38};

    // End the game if the player has 0 hp left
    if (current_level->get_player().get_life() <= 0)
        end_game = true;
    
    // Checks the collision on all the objects
    for (auto& a : current_level->get_objects())
    {
        for (auto& b : current_level->get_objects())
        {
            if ((a != b && a->collide(*b)) || (b != a && b->collide(*a)))
            {
                a->collision_handling(*b);
                b->collision_handling(*a);
            }
        }
    }

    // Updates all the objects
    for(auto& obj : current_level->get_objects())
    {   
        obj->update(delta_time);

    }

    // Remove any objects that has died
    current_level->remove_obejct();

    // Updates the current_level
    current_level->update(delta_time);

    // Check if the player has reached Berit
    check_end();
}

void Game_State :: render (RenderTarget & target)
{
    auto bounds { Score_text.getGlobalBounds () };
    auto size   { target.getSize () };

    Score_text.setPosition ((size.x - bounds.width) / 100,
                      (size.y - bounds.height) / 100);

    bounds = Life_text.getGlobalBounds ();

    Life_text.setPosition ((size.x - bounds.width) * 0.85,
                      (size.y - bounds.height) / 100);

    bounds = Life.getGlobalBounds ();

    Life.setPosition ((size.x - bounds.width) * 0.9,
                      (size.y - bounds.height) / 100);

    bounds = Score.getGlobalBounds ();

    Score.setPosition ((size.x - bounds.width) * 0.25,
                      (size.y - bounds.height) / 100);

    target.draw(background);
    target.draw(Score_text);
    target.draw(Life_text);
    target.draw(Life);
    target.draw(Score);

    for(auto& object : current_level->get_objects())         
    {
    
        target.draw(object->get_sprite());
              
    }

    target.draw(current_level->get_player().get_sprite());
}

int Game_State :: get_next_state()
{
    if (pause)
    {
        return PAUSE_STATE;
    }
    else if (end_game)
    {
        update_current_score();
        return END_STATE;
    }
    return GAME_STATE;
   
}

void Game_State::read_current_score()
{
    std::ifstream read_from {"resources/Scores/current_score.txt"};

    highscore = current_level->get_player().get_score();
    
    if(read_from.is_open())
    {   
        int tmp {};
        read_from >> tmp;
        highscore += tmp;
        read_from.close();
    }
}
void Game_State::update_current_score()
{
    read_current_score();

    std::ofstream write_to {"resources/Scores/current_score.txt"};

    if(write_to.is_open())
    {
        write_to << highscore;
        write_to.close();
    }
}

void Game_State::check_end()
{
    if(current_level->get_player().get_status())
    {
        update_current_score();

        if(levels.size() == 1)
        {
            end_game = true;
        }
        else
        {
            levels.pop_front();
            current_level = levels.front();
        }       
    }
}