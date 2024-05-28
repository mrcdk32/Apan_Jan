#include "../includes/level.h"
#include "../includes/Game_State.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Level::Level(int const lvl_number)
    :level_num{lvl_number}, objects {}, player {}, elapsed_time {}
{   
    std::ifstream read_from {"resources/levels/lvl" + std::to_string(level_num) + ".txt"};
    std::string object_string {};

    if(!read_from.is_open())
    {
        std::cerr << "Error: unable to open the file" << std::endl;
    }

    while(getline(read_from, object_string))
    {
        read_object(object_string);
    }
}

Level::~Level()
{

}

void Level::read_object(std::string const& obj_str)
{
    std::stringstream ss{obj_str};
    double x, y;
    std::string type{};
    std::string sprite_init{};

    ss >> x >> y >> type >> sprite_init;        //read objects from file and construct them into objects vector
    
    if (type == "Player")
    {
        objects.push_back(std::move(std::make_unique<Player>(type, x, y, sprite_init)));   
    }
    else if (type == "Barrel")
    {
         objects.push_back(std::move(std::make_unique<Barrel>(type, x, y, sprite_init)));
    }
    else if(type == "Gorilla")
    {
        objects.push_back(std::move(std::make_unique<Gorilla>(type, x, y, sprite_init)));
    }
    else if (type == "Platform")
    {
         objects.push_back(std::move(std::make_unique<Platform>(type, x, y, sprite_init)));
    }
    else if(type == "Collision_Box")
    {
         objects.push_back(std::move(std::make_unique<Collision_Box>(type, x, y, sprite_init)));
    }
    else if(type == "Ladder")
    {
        objects.push_back(std::move(std::make_unique<Ladder>(type, x, y, sprite_init)));
    }
    else if(type == "Berit")
    {
        objects.push_back(std::move(std::make_unique<Berit>(type, x, y, sprite_init)));
    }
    else if(type == "Hammer")
    {
        objects.push_back(std::move(std::make_unique<Hammer>(type, x, y, sprite_init)));
    }
}

std::vector<std::unique_ptr<Object>>& Level::get_objects() //Get object from level
{  
    return objects;
}
void Level::remove_obejct()           //remove object if status = false;
{
 {
    auto it = std::remove_if(objects.begin(), objects.end(), 
    [](const std::unique_ptr<Object>& obj) 
    {
        return !obj->status();
    });

    objects.erase(it, objects.end());
}
}
Player& Level::get_player() //Get player object
{
    for(auto& obj : objects)
    {
        if(obj->get_name() == "Player")
        return dynamic_cast<Player&>(*obj);
    }
    std::cerr << "no player in level ";
    exit(2);
}

Gorilla& Level::get_gorilla() //Get gorilla object
{
    for(auto& obj : objects)
    {
        if(obj->get_name() == "Gorilla")
        return dynamic_cast<Gorilla&>(*obj);
    }
    std::cerr << "no gorilla in level ";
    exit(2);
}

Berit& Level::get_berit() //get berit object B)
{
     for(auto& obj : objects)
    {
        if(obj->get_name() == "Berit")
        return dynamic_cast<Berit&>(*obj);
    }
    std::cerr << "no berit in level ";
    exit(2);
}

void Level::update(float const& delta_time)     //Update of level class that genarates barrels
{
    get_berit().set_animstate(level_num);
    
    elapsed_time += delta_time;
    if(elapsed_time >= 4.0 / level_num)
    {
        objects.push_back(std::move(std::make_unique<Barrel>("Barrel", get_gorilla().get_position().x
                        , get_gorilla().get_position().y - 20, "resources/sprites/Barrel/barrel_sprite.png")));

        elapsed_time = 0;
    }
}
