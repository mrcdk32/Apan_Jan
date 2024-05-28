#pragma once

#include "Object.h"
#include "Barrel.h"

// ==================== Apan Jan ====================

class Gorilla : public Dynamic_Object
{

enum JAN_ANIMATIONS
{
  IDLE1 = 0,
  IDLE2 = 1,
  IDLE3 = 2,
  THROW = 3,

};
public:
    Gorilla(std::string name, 
            double x, 
            double y, 
            std::string texture_file);
    ~Gorilla() = default;
    void update(float const& delta_time) override;
    void move(float const& delta_time) override;
    void collision_handling(Object & obj) override;
    const sf::FloatRect get_collision_rect() const override;
    void set_animstate(int animation);
    void update_animation() override;

private:
    int random_idle() const;
    //Animation_Engine animations;
};
