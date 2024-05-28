#include "../includes/Object.h"
#include "../includes/constants.h"
#include <cstdlib>

#include <iostream>

Object::Object( std::string name,
                double x, 
                double y, 
                std::string texture_file)
: name{name} , pos_x{x}, pos_y{y} ,texture{Manager<sf::Texture>::load(texture_file)}
{   
  sprite.setPosition(pos_x, pos_y);
  sprite.setTexture(texture);
  sprite.setScale(3, 3);
  is_alive = true;
}
bool Object::status() const
{
  return is_alive;
}
sf::Sprite Object::get_sprite() const
{
  return sprite;
}

const std::string& Object::get_name() const
{
  return name;
}

sf::Vector2f Object::get_position() const
{
  return sf::Vector2f(pos_x, pos_y);
}
const sf::FloatRect Object::get_collision_rect() const
{
  return sprite.getGlobalBounds();
}

bool Object::collide(Object const& b)
{
  return  get_collision_rect().intersects(b.get_collision_rect());
}

// ==================== Dynamic Object ====================

Dynamic_Object::Dynamic_Object(std::string name, double x, double y, std::string texture_file)
: Object {name, x, y, texture_file}, is_grounded {false}, animstate {}
{

}

void Dynamic_Object::gravity(double delta_time)
{
  if(is_grounded)
  {
    is_grounded = false;
    return;
  }

  pos_y += falling_speed * delta_time;
}

void Dynamic_Object::update_sprite()
{
  sprite.setPosition(pos_x, pos_y);
  
}

// ==================== Static Object ====================

Static_Object::Static_Object(std::string name, double x, double y, std::string texture_file)
  : Object {name, x, y, texture_file}
{
  auto size { texture.getSize () };
  sprite.setOrigin (size.x * 2.25, size.y * 2.25); // måste ändras. varför 2.25????????   sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height); <-- sätter till botten av spriten!
}

// ==================== Ladder ====================

Ladder::Ladder(std::string name, double x, double y, std::string load_texture)
  : Static_Object {name, x, y, load_texture}
{
  auto size { texture.getSize () };
  sprite.setOrigin (size.x / 2, size.y / 2);
  sprite.setScale(0.92, 0.92);

  // Creates a collision box at the top of the ladder
  top_collision.width = sprite.getGlobalBounds().width / 10;
  top_collision.height = sprite.getGlobalBounds().height / 2.0f;
  top_collision.top = sprite.getGlobalBounds().top - 5.0f;
  top_collision.left = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2;

  // Createas a collision box att the top of the ladder
  bottom_collision.width = sprite.getGlobalBounds().width / 10;
  bottom_collision.height = sprite.getGlobalBounds().height / 2.0f;
  bottom_collision.top = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2;
  bottom_collision.left = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2;
}

void Ladder::update(float const& delta_time)
{

}

void Ladder::collision_handling(Object & lhs)
{
  return;
}

const sf::FloatRect& Ladder::get_top_collision() const
{
  return top_collision;
}

const sf::FloatRect& Ladder::get_bottom_collision() const
{
  return bottom_collision;
}

// ==================== Platform ====================

Platform::Platform(std::string name, double x, double y, std::string load_texture)
  : Static_Object {name, x, y, load_texture}
{}

void Platform::update(float const& delta_time)
{

}

void Platform::collision_handling(Object & lhs)
{
  return;
}

// ==================== Collision_Box ====================

Collision_Box::Collision_Box(std::string name, double x, double y, std::string load_texture)
  : Static_Object {name, x, y, load_texture}
{
  sprite.setScale(2.7f, 2.7f);
}

void Collision_Box::update(float const& delta_time)
{

}

void Collision_Box::collision_handling(Object & lhs)
{
  return;
}

// ====================Berit================================================
Berit::Berit(std::string name, double x, double y, std::string load_texture)
: Dynamic_Object {name, x, y, load_texture}
{
  currentframe = sf::IntRect(0, 30, 30, 30);
  sprite.setTextureRect(currentframe);
  animstate = BERIT_ANIMATIONS::LEVEL1;
  sf::FloatRect spriteBounds{10,10, 10, 10};
  sf::Vector2f size(spriteBounds.width, spriteBounds.height);
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
}
void Berit::collision_handling(Object & lhs)
 {
    return;
 }

 void Berit::update(float const& delta_time)
{
  update_animation();
}

void Berit::move(float const& delta_time)
{

}

void Berit::set_animstate(int state)
{
  animstate = state;
}

const sf::FloatRect Berit::get_collision_rect() const
{
  sf::FloatRect hitbox{10, 5, 10, 22};
  return sprite.getTransform().transformRect(hitbox);
}

void Berit::update_animation()
{
      if(animstate == BERIT_ANIMATIONS::LEVEL1)
    {
      if(animationtime.getElapsedTime().asSeconds() >= 0.9f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 30.f;
      currentframe.left += 30.f;

      if(currentframe.left >= 60)
      {
        currentframe.left = 0;
      }
      animationtime.restart();
      sprite.setTextureRect(currentframe);
      }
    }
    else if(animstate == BERIT_ANIMATIONS::LEVEL2)
    {
      if(animationtime.getElapsedTime().asSeconds() >= 0.9f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 0.f;
      currentframe.left += 30.f;

      if(currentframe.left >= 120)
      {
        currentframe.left = 0;
      }
      animationtime.restart();
      sprite.setTextureRect(currentframe);
      }
    }
    else if(animstate == BERIT_ANIMATIONS::LEVEL3)
    {
      if(animationtime.getElapsedTime().asSeconds() >= 0.8f)
      {
      //currentframe = IntRect(coordinates.at(0).first,coordinates.at(0).second, 36, 36);
      currentframe.top = 90.f;
      currentframe.left += 30.f;

      if(currentframe.left >= 90)
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

// ========================= Hammer =============================
Hammer::Hammer(std::string name, double x, double y, std::string load_texture)
  : Static_Object {name, x, y, load_texture}
{
  auto size { texture.getSize () };
   sprite.setOrigin (size.x / 2, size.y / 2);
}

void Hammer::update(float const& delta_time)
{

}

void Hammer::collision_handling(Object & lhs)
{
  if(lhs.get_name() == "Player")
  {
    is_alive = false;
  }
}
