#include "../includes/Gorilla.h"
#include <iostream>

// ==================== Gorilla ====================

Gorilla::Gorilla(std::string name, double x, double y, std::string load_texture)
  : Dynamic_Object {name, x, y, load_texture}
{
  currentframe = sf::IntRect(0,0,50,50);
  sprite.setTextureRect(currentframe);
  sf::FloatRect spriteBounds{2,2, 46, 34};
  sf::Vector2f size(spriteBounds.width, spriteBounds.height);
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
  //sets the initial bound of the sprite from the spritesheet and sets the origin point to the feet 

}
void Gorilla::update(float const& delta_time) //The gorilla has three random idle states
{
    if(delta_time >= 1.6 )
  {
    animstate = random_idle();
  }

  update_animation();
  update_sprite();
}

const sf::FloatRect Gorilla::get_collision_rect() const  //custom hitbox
{
  sf::FloatRect hitbox{10, 10, 30, 30};
  return sprite.getTransform().transformRect(hitbox);
}

void Gorilla::move(float const& delta_time)
{

}

void Gorilla::collision_handling(Object & obj) 
{

}

int Gorilla::random_idle() const
{
  
   int rand_num = rand() % 100; // generate a random number between 0 and 99
    int animstate = 0;          // default to first idle animation
    if (rand_num > 90) {        // default idle animation will play 90% of the time
        animstate = rand() % 2 + 1; // generate a random number between 1 and 2
    }

    return animstate;
}

void Gorilla::update_animation()
{
    if(animstate == JAN_ANIMATIONS::IDLE1)
    {
     
      currentframe.top = 0.f;
      currentframe.left = 0;
      sprite.setTextureRect(currentframe);
      
    }
    else if(animstate == JAN_ANIMATIONS::IDLE2)
    {
    if(animationtime.getElapsedTime().asSeconds() >= 0.4f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 0.f;
      currentframe.left += 50.f;

      if(currentframe.left >= 200)
      {
        currentframe.left = 0;
      }
      animationtime.restart();
      sprite.setTextureRect(currentframe);
      }
    }
    else if(animstate == JAN_ANIMATIONS::IDLE3)
    {
       if(animationtime.getElapsedTime().asSeconds() >= 0.4f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 150.f;
      currentframe.left += 50.f;

      if(currentframe.left >= 200)
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

