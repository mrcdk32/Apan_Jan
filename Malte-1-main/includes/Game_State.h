#pragma once

#include "State.h"
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "level.h"
#include <deque>

#include <vector>

class Game_State : public State
{
public:

    Game_State ();
    ~Game_State ();

    void handle_event (sf::Event event) override;
    void update () override;
    void render (sf::RenderTarget & target) override;
    virtual int get_next_state() override;
    void check_end();
    void update_current_score();
    void read_current_score();


private:
    bool end_game;
    bool pause;
    sf::Text Score_text{};
    sf::Text Life_text{};
    sf::Text Life{};
    sf::Text Score{};
    int menu_selection {};
    std::vector<sf::Text> menu_vector {};
    std::deque<Level*> levels;
    Level* current_level;
    sf::Clock timer;
    float delta_time;
    float pause_time;
    float elapsed_time {};
    int highscore;
};
