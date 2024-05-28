#pragma once
#include "State.h"
#include <vector>
#include <fstream>


class End_State : public State
{
public:

    End_State ();

    void handle_event (sf::Event event) override;
    void update () override;
    void render (sf::RenderTarget & target) override;
    virtual int get_next_state() override;

private:
    sf::Text game_over_text;
    sf::Text next_text;
    sf::Text score;
    sf::Text high_score_text;
    sf::Text high_score;
    bool go_to_menu;
    int current_score;
    int highscore;
    std::ifstream read_from;
    std::ofstream write_to;
};