#include "../includes/State.h"

State :: State ()
    :background {}, texture {}
{
    std::string file = "resources/fonts/Pixel_NES.otf"; 
    if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");
}