#include "../includes/constants.h"
#include "../includes/Game.h"
#include "../includes/Menu_State.h"
#include "../includes/Game_State.h"
#include "../includes/Pause_State.h"
#include "../includes/End_State.h"

#include <iostream> //testing

using namespace sf;

/*
 * Initialize the window and the first state is Menu_State.
 *
 * The constructor of RenderWindow takes a 'VideoMode'
 * which defines the width, height and bits per pixel
 * (default 32), a title which should be visible in
 * the titlebar of the windows, as well as a style flag.
 * The style flag is a bit mask (i.e. a value where
 * each bit represents a property) of properties we
 * want our window to have. If we do not care,
 * we can omitt this argument or use sf::Style::Default.
 */
Game :: Game (std::string const & title,
              unsigned            width,
              unsigned            height)
        : window { VideoMode { width, height },
        title, Style::Titlebar | Style::Close },
                   current_state{ MENU_STATE },
          running { true }
{
    // Insert all sates you want in your game in the states map
    states.insert(std::pair<int,
            std::unique_ptr<State>>({MENU_STATE,
                                     std::make_unique<Menu_State>()}));
    states.insert(std::pair<int,
                  std::unique_ptr<State>>({PAUSE_STATE,
                                           std::make_unique<Pause_State>()}));

    states.insert(std::pair<int,
                  std::unique_ptr<State>>({END_STATE,
                                           std::make_unique<End_State>()}));
}


void Game :: start ()
{
    // The clock is used to measure of long each iteration took
    // this is used to keep the framerate as steady as possible.
    Clock clock { };
    while ( running )
    {
        // Handle user events e.g. mouse click or key pressed
        handle_events();
        // Let the current state do its update
        states.at(current_state) -> update();

        /*
         * clear fills the entire window with one color
         * (by default black) thus overwriting everything
         * that was drawn before.
         *
         * If we do not perform this step we allow for weird
         * graphical artifacts to show up.
         */
        window.clear();
           
        // let the current state render itself onto the window
        states.at(current_state) -> render(window);

        /*
         * No drawn pixels will be shown in the window
         * until this function is called.
         *free(): double free detected in tcache 2 Aborted (core dumped)
         * All drawing operations are performed on a
         * hidden buffer in memory, so if we want them
         * to actually show up on the screen we have
         * make sure that the window switches to drawing
         * that buffer instead of its current one.
         * (This technique is called 'double buffering')
         */
        window.display();

        /*
         * When all logic and rendering has been performed
         * we are now ready to update the current_state
         */
         current_state = states.at(current_state)->get_next_state();

         if(current_state == MENU_STATE && states.size() == 4)
         {
            states.erase(GAME_STATE);
         }
         else if(current_state == GAME_STATE && states.size() < 4)
         {
            states.insert(std::pair<int, std::unique_ptr<State>>({GAME_STATE, std::make_unique<Game_State>()}));
         }
         else if(current_state == EXIT)
         {
            running = false;
         }
         else if(current_state == END_STATE && states.size() == 4)
         {
            states.erase(GAME_STATE);
         }

        /*
         * Wait if we still haven't reached the target
         * time for a frame.
         */
        delay (clock);
    }

    std::ofstream write_to {"resources/Scores/current_score.txt"};
    write_to.close();
}


void Game :: handle_events ()
{
    /*
     * event is an object which contains all
     * relevant information for an event that
     * occured in the window (i.e. key-pressed,
     * mouse clicks etc.).
     *
     * The function 'pollEvent' takes the next
     * event in the event queue and places it
     * in the 'event' variable so that we can
     * read what that event was.
     *
     * While there are events in event queue
     * 'pollEvent' will return true.
     */
    Event event;
    while ( window.pollEvent (event) )
    {
        // Check if the window has been closed.
        // This event fires whenever the user
        // presses the X icon, or if the operating
        // system kills it.
        if ( event.type == Event::Closed )
            running = false;

        // send the event to 'state'
        states.at(current_state) -> handle_event (event);
    }
}

void Game :: delay (sf::Clock & clock) const
{
    sleep (milliseconds (1000.0 / fps) - clock.getElapsedTime ());
    clock.restart ();
}