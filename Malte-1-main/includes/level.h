#ifndef LEVEL_H
#define LEVEL_H
#include "Object.h"
#include "Barrel.h"
#include "Player.h"
#include "Gorilla.h"
#include <vector>
#include "Player.h"

class Level
{

public:

    Level(int const lvl_number = 1);
    ~Level();

    void remove_obejct();
    std::vector<std::unique_ptr<Object>>& get_objects();

    template <typename T>
    void add_to_level(T const& obj)
    {
        objects.push_back(std::make_unique<T>(obj));
    }

    Player& get_player();
    Gorilla& get_gorilla();
    Berit& get_berit();

    void update(float const& delta_time);

private:

    void read_object(std::string const& obj_str);

    int level_num{};
    std::vector<std::unique_ptr<Object>> objects{};
    std::unique_ptr<Player> player;
    float elapsed_time;
};
#endif 
