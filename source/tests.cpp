#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include <glm/vec3.hpp>

//Aufgabe 5.2
TEST_CASE ("radius-center-test", "[sphere]")
{
  Sphere sphere1; //Standardkonstruktor 
  REQUIRE (sphere1.get_center().x == 0.0f);
  REQUIRE (sphere1.get_center().y == 0.0f);
  REQUIRE (sphere1.get_center().z == 0.0f);
  REQUIRE (sphere1.get_radius() == 0.5f);

  Sphere sphere2 {{0.8f,0.3f,0.5f}, "Name2", {0.5f,0.3f,1.0f}, 8.0f};
  REQUIRE (sphere2.get_center().x == 0.5f);
  REQUIRE (sphere2.get_center().y == 0.3f);
  REQUIRE (sphere2.get_center().z == 1.0f);
  REQUIRE (sphere2.get_radius() == 8.0f);
}

TEST_CASE ("sphere-area-test", "[sphere]")
{
  Sphere sphere1;
  REQUIRE (sphere1.area() == Approx(3.14f).epsilon(0.01));
  Sphere sphere2 {8.0f};
  REQUIRE (sphere2.area() == Approx(804.24f).epsilon(0.01));
}

TEST_CASE ("sphere-volume-test", "[sphere]")
{
  Sphere sphere1;
  REQUIRE (sphere1.volume() == Approx(0.523f).epsilon(0.01));
  Sphere sphere2 {8.0f};
  REQUIRE (sphere2.volume() == Approx(2144.66f).epsilon(0.01));
}

TEST_CASE ("min-max-test", "[box]")
{
  Box box1; 
  REQUIRE (box1.get_min().x == 0.0f);
  REQUIRE (box1.get_min().y == 0.0f);
  REQUIRE (box1.get_min().z == 0.0f);
  REQUIRE (box1.get_max().x == 1.0f);
  REQUIRE (box1.get_max().y == 1.0f);
  REQUIRE (box1.get_max().z == 1.0f);

  Box box2 {{0.8f,0.3f,0.5f}, "Name3", {0.5f,0.3f,1.0f}, {5.0f,3.0f,10.0f}}; 
  REQUIRE (box2.get_min().x == 0.5f);
  REQUIRE (box2.get_min().y == 0.3f);
  REQUIRE (box2.get_min().z == 1.0f);
  REQUIRE (box2.get_max().x == 5.0f);
  REQUIRE (box2.get_max().y == 3.0f);
  REQUIRE (box2.get_max().z == 10.0f);
}

TEST_CASE ("box-area-test", "[box]")
{
  Box box1;
  REQUIRE (box1.area() == Approx(6.0f).epsilon(0.01));
  Box box2 {{0.8f,0.3f,0.5f}, "Name4", {0.5f,0.3f,1.0f}, {5.0f,3.0f,10.0f}}; 
  REQUIRE (box2.area() == Approx(153.9f).epsilon(0.01));
}

TEST_CASE ("box-volume-test", "[box]")
{
  Box box1;
  REQUIRE (box1.volume() == Approx(1.0f).epsilon(0.01));
  Box box2 {{0.8f,0.3f,0.5f}, "Name4", {0.5f,0.3f,1.0f}, {5.0f,3.0f,10.0f}}; 
  REQUIRE (box2.volume() == Approx(109.35f).epsilon(0.01));
}


int main(int argc, char *argv[])
{
  //Aufgabe 5.5 

  Sphere sphere1;
  std::cout << sphere1 << "\n";

  Sphere sphere2 {{0.8f,0.3f,0.5f}, "Kugel 2", {0.5f,0.3f,1.0f}, 8.0f};
  std::cout << sphere2 << "\n"; 

  Box box1; 
  std::cout << box1 << "\n"; 

  Box box2 {{0.8f,0.3f,0.5f}, "Box 2", {0.5f,0.3f,1.0f}, {5.0f,3.0f,10.0f}}; 
  std::cout << box2 << "\n";



  return Catch::Session().run(argc, argv);
}
