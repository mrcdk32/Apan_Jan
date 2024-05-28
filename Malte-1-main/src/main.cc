#include "../includes/Game.h"
#include "../includes/constants.h"
#include "../includes/Object.h"
#include <iostream>
#include <vector>

using namespace sf;
int main ()
{
    // We only want the main function to start the Game and then run it
    Game g { "Apan Jan", screen_width, screen_height };
    g.start ();
    
return 0;
}
