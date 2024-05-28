#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

#include "State.h"

class Game {

public:
    Game (std::string const & title, unsigned width, unsigned height);
    void start ();

private:
    
    sf::RenderWindow window;


    /*
     * Container for all states in the game.
     * Current_state keeps track on the current state
     */
    std::map<int, std::unique_ptr<State>> states;
    int current_state;


    /*
      If true, then the game should keep on run, otherwise the next
      iteration of the game loop will not run.
    */
    bool running;
    void handle_events(); 
    void delay (sf::Clock & clock) const;
};

#endif // GAME_H