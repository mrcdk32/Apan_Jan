#pragma once

#include "Object.h"

// ==================== Player ====================

class Player : public Dynamic_Object
{

enum PLAYER_ANIMATIONS
{
  IDLE_RIGHT = 0, 
  IDLE_LEFT = 1,
  WALKING_RIGHT = 2,
  WALKING_LEFT = 3, 
  CLIMBING_UP = 4, 
  CLIMBING_DOWN = 5, 
  JUMPING_RIGHT = 6,
  JUMPING_LEFT = 7, 
  ATTACK_RIGHT = 8,
  ATTACK_LEFT = 9,
  ATTACK_RIGHT_RUN = 11,
  ATTACK_LEFT_RUN = 12,
  DEATH = 13
};
public:

    Player(std::string name, 
           double x, 
           double y, 
           std::string texture_file);
    ~Player() = default;

    void update(float const& delta_tim) override;
    void move(float const& delta_time) override;
    void collision_handling(Object & lhs) override;
    const sf::FloatRect get_collision_rect() const override; 
    void update_animation() override; 
    void hit_border();
    bool is_alive() const;
    int get_life() const;
    bool get_status() const;
    void increment_point(int ammount = 100);
    void decrement_life();
    bool powerup_active();
    int get_score();
    

private:

    bool collide_with_ladder(Object & obj);
    bool Onplatform(Object & obj);

    int lives;
    //Animation_Engine animations;
    float powerup_time{};
    bool powerup;
    bool facing_right;
    int score;
    bool is_jumping;
    float jump_timer;
    float jumpheight;
    bool touching_ladder;
    bool touching_berit{};
    bool touching_platform;
    
};