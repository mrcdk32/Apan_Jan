#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"

class Pause_State: public State
{
public:
    Pause_State ();

    virtual void handle_event (sf::Event event) override;
    virtual void update () override;
    virtual void render (sf::RenderTarget & taget) override;
    virtual int get_next_state() override;


private:

    sf::Text& get_text();
    /*
     * sf::Text is a drawable object representing a string.
     *
     * sf::Text can be drawn to any RenderTarget as long as
     * a font and a string is supplied.
     *
     * It works like a sf::Sprite but represents text instead
     * of an image.
     */
    sf::Text resume_text;
    sf::Text quit_menu_text;
    int menu_selection {};
    std::vector<sf::Text> menu_vector {};


    /*
     * Flag to determine wheter or not the 'enter' key has been
     * pressed (see Menu_State.cpp for details).
     */
    bool resume;
    bool exit_menu;


  
};