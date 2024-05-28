#pragma once

#include "Object.h"
#include "Player.h"

// ==================== Barrel ====================

class Barrel : public Dynamic_Object
{
enum BARREL_ANIMATIONS
{
  ROLLING = 0,
  ROLLING_DOWN_LADDER  = 1
};
public:
    Barrel(std::string name, 
           double x, 
           double y, 
           std::string texture_file);
    ~Barrel() = default;

    void update(float const& delta_time) override;
    void move(float const& delta_time) override;
    const sf::FloatRect get_collision_rect() const override;
    bool is_jumped_over(Player& player);
    void collision_handling(Object & lhs) override;
    void hit_border();
    void update_animation();
    
    

private:
    bool touching_ladder;
    bool point_given{};
    //Animation_Engine animations;
    bool life_decremented{};
    float speed;
    bool move_right;
    bool move_down;

};