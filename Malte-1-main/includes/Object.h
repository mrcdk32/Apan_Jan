#pragma once

#include <SFML/Graphics.hpp>
#include "../src/Manager.cc"
#include <string>
#include <vector>

class Object
{
public:
    Object(std::string name, 
           double   x,
           double   y,
           std::string texture_file);
    ~Object() = default;
    
    virtual void update(float const& delta_time) = 0;
    virtual void collision_handling (Object & lhs) = 0; //
    sf::Sprite get_sprite() const;
    const std::string& get_name() const;
    sf::Vector2f get_position() const; 
    virtual const sf::FloatRect get_collision_rect() const; //Return a rectangle that can be later used to check for collisions with other objects
    bool collide(Object const& b);
    bool status() const; 

protected:
    std::string name;
    double pos_x;
    double pos_y;
    sf::Texture texture;
    sf::Sprite sprite;
    bool is_alive;
};

// ==================== Dynamic Object ====================

class Dynamic_Object : public Object
{
public:
    Dynamic_Object( std::string name, 
                    double x, 
                    double y, 
                    std::string texture_file );
    ~Dynamic_Object() = default;

    virtual void update(float const& delta_time) = 0;
    virtual void move(float const& delta_time) = 0;
    virtual void collision_handling(Object & lhs) = 0;
    void gravity(double delta_time);
    void update_sprite();
    virtual void update_animation() = 0;
    

protected:
    bool is_grounded;
    int animstate;

    sf::IntRect currentframe;
    sf::Clock animationtime{};
};

// ==================== Static Object ====================

class Static_Object : public Object
{
public:
    Static_Object(  std::string name, 
                    double x, 
                    double y,
                    std::string texture_file );
    ~Static_Object() = default;

private:

};

// ==================== Ladder ====================

class Ladder : public Static_Object
{
public:
  Ladder(std::string name,
	 double x,
	 double y, 
	 std::string load_texture);
   ~Ladder () = default;

  void update(float const& delta_time) override;
  void collision_handling(Object & lhs) override;
  const sf::FloatRect& get_top_collision() const;
  const sf::FloatRect& get_bottom_collision() const;

private:
  sf::FloatRect top_collision;
  sf::FloatRect bottom_collision;
};

// ==================== Platform ====================

class Platform : public Static_Object
{
public:
  Platform(std::string name,
	   double x,
	   double y, 
	   std::string load_texture);
     ~Platform() = default;
    
  void update(float const& delta_time) override;
  void collision_handling(Object & lhs) override;

private:
};

class Collision_Box : public Static_Object
{
public:
  Collision_Box(std::string name,
	   double x,
	   double y, 
	   std::string load_texture);
     ~Collision_Box() = default;
    
  void update(float const& delta_time) override;
  void collision_handling(Object & lhs) override;

private:
};

// ==================== Berit ====================
class Berit : public Dynamic_Object
{

enum BERIT_ANIMATIONS
{
  LEVEL1 = 1,
  LEVEL2 = 2,
  LEVEL3 = 3,
  LEVEL4 = 4
};
public:
    Berit(std::string name,
             double x,
             double y, 
             std::string load_texture);
    ~Berit() = default;
    
    void update(float const& delta_time) override;
    void move(float const& delta_time) override;
    void collision_handling(Object & lhs) override;
    void set_animstate(int state);
    void update_animation() override;
  const sf::FloatRect get_collision_rect() const override;

    private:
    //Animation_Engine animations;

};


// ==================== Hammer ====================
class Hammer : public Static_Object
{
public:
  Hammer(std::string name,
	   double x,
	   double y, 
	   std::string load_texture);
  ~Hammer() = default;
    
  void update(float const& delta_time) override;
  void collision_handling(Object & lhs) override;
};