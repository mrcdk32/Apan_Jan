#include "../includes/Barrel.h"
#include "../includes/constants.h"

#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

// ==================== Barrel ====================

Barrel::Barrel(std::string name, double x, double y, std::string load_texture)
  :Dynamic_Object {name, x, y, load_texture}, move_right {true}, move_down {}, speed {100}, touching_ladder {}
{
  currentframe = sf::IntRect(0,0,16,16);
  sprite.setTextureRect(currentframe);
  sprite.setScale(2.5, 2.5);
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
}

void Barrel::update(float const& delta_time)
{
  move(delta_time);
  update_animation();
  if(!touching_ladder) 
  gravity(delta_time);
  update_sprite();
  hit_border();
}

int generate_random()     //Generate random number to choose if we go down the ladder or not
{
  std::random_device rand;
  std::mt19937 engine(rand());
  std::uniform_int_distribution<int> random_value(0, 100);

  return random_value(engine);
}

void Barrel::move(float const& delta_time) //Handle movement for barrel
{
  if(touching_ladder && move_down)
  {
    pos_y += speed * delta_time;
  }
  else if(move_right && is_grounded)
  {
    pos_x += speed * delta_time;
  }
  else if(!move_right && is_grounded)
  {
    pos_x -= speed * delta_time;
  }

  touching_ladder = false;
}

const sf::FloatRect Barrel::get_collision_rect() const //custom hitbox
{
  sf::FloatRect hitbox{8, -9, 2, 23};
  return sprite.getTransform().transformRect(hitbox);
}

bool Barrel::is_jumped_over(Player& player) {
    sf::Vector2f player_position = player.get_position();
    sf::Vector2f barrel_position = this->get_position();
    
    return player_position.y < barrel_position.y;

}

void Barrel::collision_handling(Object & lhs) //collision handling for barrel
{
  if(lhs.get_name() == "Platform" && !touching_ladder)
  {
    is_grounded = true;
    animstate = BARREL_ANIMATIONS::ROLLING;
  }
  else if(lhs.get_name() == "Ladder")
  {
    if(get_collision_rect().intersects((dynamic_cast<Ladder*>(&lhs)->get_top_collision())) && !touching_ladder)
    {
      touching_ladder = true;

      srand(time(NULL));
      int random = rand() % 101;
  
      if(random >= 50)
      {
        animstate = BARREL_ANIMATIONS::ROLLING_DOWN_LADDER;
        move_down = true;
        is_grounded = false;
      }
      else
      {
        animstate = BARREL_ANIMATIONS::ROLLING;
        move_down = false;
        is_grounded = true;
      }
    }
    else if(get_collision_rect().intersects((dynamic_cast<Ladder*>(&lhs)->get_bottom_collision())) && !is_grounded)
    {
      animstate = BARREL_ANIMATIONS::ROLLING;
      is_grounded = true;
      move_down = false;
      move_right = !move_right;
    }
  }
  else if(lhs.get_name() == "Collision_Box")
  {
    is_alive = false;
  }
  else if(Player* player = dynamic_cast<Player*>(&lhs))  //create pointer if object is Player-class otherwise nullptr
  {
    if(is_jumped_over(*player) && point_given == false) 
    {
      point_given = true;
      player->increment_point();
        //Add points to the player
    }

    else if(player->powerup_active() == true && point_given == false)
    {
      point_given = true;
      player->increment_point(500);
      is_alive = false;
        //Add points to the player and destory barrel
    }
    else if( player->powerup_active() == true && point_given == false)
    {
      is_alive = false;
      //destroy barrel
    }
    else if(!is_jumped_over(*player) && player->powerup_active() == false && life_decremented == false) 
    {
      player->decrement_life();
      life_decremented = true;
      //take away life from player
    }
    
    player = nullptr;
  }
  
 
}
void Barrel::hit_border()  //If barrel hits the border. Change direction
{
    if ((pos_x) >= screen_width - 10)
    {
        move_right = !move_right;
    }
    else if ((pos_x - 14) <= 0)
    {
      move_right = !move_right;
    }
}

void Barrel::update_animation()
{
    if(animstate == BARREL_ANIMATIONS::ROLLING)
    {
    if(animationtime.getElapsedTime().asSeconds() >= 0.2f)
    {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 0.f;
      currentframe.left += 16.f;

      if(currentframe.left >= 32)
      {
        currentframe.left = 0;
      }
      animationtime.restart();
      sprite.setTextureRect(currentframe);
      }
    }
    else if(animstate == BARREL_ANIMATIONS::ROLLING_DOWN_LADDER)
    {
      if(animationtime.getElapsedTime().asSeconds() >= 0.2f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 16.f;
      currentframe.left += 16.f;

      if(currentframe.left >= 32)
      {
        currentframe.left = 0;
      }
      animationtime.restart();
      sprite.setTextureRect(currentframe);
      }
    }
    else
    {
    animationtime.restart();
    }
}
