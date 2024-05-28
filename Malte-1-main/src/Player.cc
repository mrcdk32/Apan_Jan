#include "../includes/Player.h"
#include "../includes/constants.h"
#include <string>
#include <iostream>
#include <iostream>

// ==================== Player ====================

Player::Player(std::string name, double x, double y, std::string texture_file)
  : Dynamic_Object {name, x, y, texture_file},  lives {3}, powerup {false}, facing_right{true}, score {}, is_jumping {}, jumpheight {}, touching_platform {}, touching_berit {}
{
  currentframe = sf::IntRect(0,0,36,36);
  sprite.setTextureRect(currentframe);
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
}

void Player::update(float const& delta_time) //update player
{
    move(delta_time);
    gravity(delta_time);
    update_animation();
    hit_border();   
    update_sprite();
    
    if(powerup_time >= 10.0f && powerup == true)
    {
      std::cout << "hammer time" << std::endl;
      powerup = false;
      powerup_time = 0;
    }
    else if( powerup == true)
    {
      powerup_time += delta_time; 
    }
}

void Player::move(float const& delta_time) //Handle movement of player and which animation to use
{
  if(sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W) ||  sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A) 
  || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S) ||  sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D))
  {
    if( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W) && touching_ladder && !powerup)
    {
      animstate = PLAYER_ANIMATIONS::CLIMBING_UP;
      pos_y -= (player_speed * 2) * delta_time;
    }

    if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A) )
    {
      if(powerup == false)
      {
      facing_right = false;
      animstate = PLAYER_ANIMATIONS::WALKING_LEFT;
      pos_x -= player_speed * delta_time;
      
      }
       else if(powerup == true)
      {
      facing_right = false;
      animstate = PLAYER_ANIMATIONS::ATTACK_LEFT_RUN;
      
      pos_x -= player_speed * delta_time;
      }
      
    }

    if( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S) && touching_ladder && !touching_platform && !powerup)
    {
      animstate = PLAYER_ANIMATIONS::CLIMBING_DOWN;
		  pos_y += (player_speed - 50) * delta_time;
    }
  
    if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D) )
    {
      if(powerup == false)
      {
      facing_right = true;
      animstate = PLAYER_ANIMATIONS::WALKING_RIGHT;
      
      pos_x += player_speed * delta_time;
      
      }
      else if(powerup == true)
      {
        facing_right = true;
      animstate = PLAYER_ANIMATIONS::ATTACK_RIGHT_RUN;
      
      pos_x += player_speed * delta_time;
      }
    }
  }

  else if(is_jumping == false && is_grounded == true && powerup == false)
  {
    
       if(facing_right == true)
        {
          animstate = PLAYER_ANIMATIONS::IDLE_RIGHT;
        }
        else
        {
          animstate = PLAYER_ANIMATIONS::IDLE_LEFT;

        }
  }
  else if( is_jumping == false && is_grounded == true && powerup == true)
  {
    if(facing_right == true)
        {
          animstate = PLAYER_ANIMATIONS::ATTACK_RIGHT;
        }
        else
        {
          animstate = PLAYER_ANIMATIONS::ATTACK_LEFT;

        }
  }
    
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Space) && is_grounded && powerup == false)
    {
      is_jumping = true;
      is_grounded = false;
    }

    if(is_jumping)
    {
      if(facing_right == true)
        {
          animstate = PLAYER_ANIMATIONS::JUMPING_RIGHT;
        }
        else
        {
          animstate = PLAYER_ANIMATIONS::JUMPING_LEFT;
        }
      if(jumpheight <= 130)
      {
        

        pos_y -= jump_speed * delta_time;
        jumpheight += jump_speed * delta_time;
      }
      else
      {
        is_jumping = false;
        jumpheight = 0;
        
      }
      
    }
  touching_ladder = false;
}


void Player::collision_handling(Object& obj) //Do stuff with the colliding object
{
	if (obj.get_name() == "Barrel")
	{

	}

  else if(obj.get_name() == "Gorilla")
  {
    lives = 0;
  }
	else if (obj.get_name() == "Hammer")
	{
    //powerup_time += delta_time;
		powerup = true;

	}
	else if (obj.get_name() == "Ladder")
	{
    touching_ladder = true;

    if(get_collision_rect().intersects((dynamic_cast<Ladder*>(&obj)->get_top_collision()))) //What collision box is the player touching? bootom or top
    {
      touching_platform = false;
    }
    else if(get_collision_rect().intersects((dynamic_cast<Ladder*>(&obj)->get_bottom_collision())))
    {
      touching_platform = true;
    }
	}
	else if (obj.get_name() == "Platform")
	{
    is_grounded = true;
    if (!touching_ladder)
		{
			is_grounded = true;

      if(collide_with_ladder(obj))
      {
        is_grounded = false;
      }
    }

	}
  else if (obj.get_name() == "Berit")
    {
      sf::sleep(sf::seconds(2));
      touching_berit = true;
    }
}

const sf::FloatRect Player::get_collision_rect() const //return custom hitbox
{
  sf::FloatRect hitbox{};
  if(powerup == false)
  {
  hitbox = sf::FloatRect{11, 12, 9, 16};
  }
  else
  {
  hitbox = sf::FloatRect{4, 12, 28, 16};
  }
  return sprite.getTransform().transformRect(hitbox);
}

bool Player::collide_with_ladder(Object & obj) //Check if the player is in the middle of a ladder
{
  sf::FloatRect platformBounds = obj.get_collision_rect();
  sf::FloatRect playerBounds = get_collision_rect();
  playerBounds.width / 6;
  playerBounds.height / 2,
  playerBounds.left += 10;
  playerBounds.top -= 10; 
  return playerBounds.intersects(platformBounds);

}

void Player::hit_border()  //Check if player has hit border of the screen
{
    if ((pos_x) >= 745)
    {
        pos_x = 744;
    }
    if ((pos_x - 14) <= 0)
    {
        pos_x = 14;
    }
}

void Player::update_animation()
{
  if(animstate == PLAYER_ANIMATIONS::IDLE_RIGHT || animstate == PLAYER_ANIMATIONS::IDLE_LEFT)
    {
    if(animstate == PLAYER_ANIMATIONS::IDLE_LEFT)
    {
    currentframe.top = 36.f;
    }
    else
    {
    currentframe.top = 0.f;
    }
    currentframe.left = 0;
    sprite.setTextureRect(currentframe);
  
    }
   else if(animstate == PLAYER_ANIMATIONS::WALKING_RIGHT || animstate == PLAYER_ANIMATIONS::WALKING_LEFT)
    {
    if(animationtime.getElapsedTime().asSeconds() >= 0.1f)
    {
    if(animstate == PLAYER_ANIMATIONS::WALKING_LEFT)
      {
      currentframe.top = 36.f;
      }
    else
      {
      currentframe.top = 0.f;
      }
    currentframe.left += 36.f;

    if(currentframe.left >= 108)
    {
        currentframe.left = 0;
    }
    animationtime.restart();
    sprite.setTextureRect(currentframe);
    }
  }
  else if(animstate == PLAYER_ANIMATIONS::CLIMBING_DOWN)
  {
     if(animationtime.getElapsedTime().asSeconds() >= 0.1f)
    {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 108.f;
      currentframe.left += 36.f;

      if(currentframe.left >= 72)
      {
        currentframe.left = 0.f;
      }
    animationtime.restart();
    sprite.setTextureRect(currentframe);
    }
  }
  else if(animstate == PLAYER_ANIMATIONS::CLIMBING_UP)
  {
       if(animationtime.getElapsedTime().asSeconds() >= 0.1f)
    {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 72.f;
      currentframe.left += 36.f;

      if(currentframe.left >= 72)
      {
        currentframe.left = 0.f;
      }
    animationtime.restart();
    sprite.setTextureRect(currentframe);
    }
  }
  else if(animstate == PLAYER_ANIMATIONS::JUMPING_LEFT || animstate == PLAYER_ANIMATIONS::JUMPING_RIGHT)
  {
    if(animstate == PLAYER_ANIMATIONS::JUMPING_LEFT)
    {
    currentframe.top = 36.f;
    }
    else
    {
    currentframe.top = 0.f;
    }
    currentframe.left = 72;
    sprite.setTextureRect(currentframe);
  }
  else if(animstate == PLAYER_ANIMATIONS::ATTACK_RIGHT || animstate == PLAYER_ANIMATIONS::ATTACK_LEFT)
  {
    if(animationtime.getElapsedTime().asSeconds() >= 0.2f)
    {
     if(animstate == PLAYER_ANIMATIONS::ATTACK_LEFT)
    {
    currentframe.top = 180.f;
    }
    else
    {
    currentframe.top = 144.f;
    }
     currentframe.left += 36.f;

    if(currentframe.left >= 72)
    {
        currentframe.left = 0;
    }
    animationtime.restart();
    sprite.setTextureRect(currentframe);
    }
  }
  else if(animstate == PLAYER_ANIMATIONS::ATTACK_RIGHT_RUN || animstate == PLAYER_ANIMATIONS::ATTACK_LEFT_RUN)
  {
    if(animationtime.getElapsedTime().asSeconds() >= 0.2f)
    {
     if(animstate == PLAYER_ANIMATIONS::ATTACK_LEFT_RUN)
    {
    currentframe.top = 180.f;
    }
    else
    {
    currentframe.top = 144.f;
    }

    currentframe.left += 36.f;

    if(currentframe.left >= 144)
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

bool Player::is_alive() const
{
  return lives == 0;
}

int Player::get_life() const
{
  return lives;
}

bool Player::get_status() const
{
  return touching_berit;
}

void Player::increment_point(int ammount)
{
  score = score + ammount;
}

void Player::decrement_life()
{
  --lives;
  pos_x = 30;
  pos_y = 972;
}

bool Player::powerup_active()
{
  return powerup;
}


int Player::get_score()
{
  return score;
}
