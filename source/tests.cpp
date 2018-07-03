#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

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

TEST_CASE ("intersect_ray_sphere","[intersect]")
{
    //Ray
    glm::vec3 ray_origin {0.0f, 0.0f, 0.0f};
    glm::vec3 ray_direction {0.0f, 0.0f, 1.0f};

    //Sphere
    glm::vec3 sphere_center {0.0f, 0.0f, 5.0f};
    float sphere_radius {1.0f};

    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
            ray_origin, ray_direction,
            sphere_center,
            sphere_radius * sphere_radius, 
            distance);
    REQUIRE (distance == Approx(4.0f));
}

TEST_CASE ("intersect_ray_sphere_1", "[intersect]")
{
  Sphere sphere1 {glm::vec3{0.0f, 0.0f, 5.0f}, 1.0f};
  Ray ray1 {};
  float distance1=0.0f; 
  auto result = sphere1.intersect(ray1,distance1);
  REQUIRE (result==false);
  REQUIRE (distance1==Approx(-4.0f));
}

TEST_CASE ("intersect_ray_sphere_2", "[intersect]")
{
  Sphere sphere2 {glm::vec3{0.0f, 0.0f, 5.0f}, 1.0f};
  Ray ray2 {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}};
  float distance2=0.0f; 
  auto result2 = sphere2.intersect(ray2,distance2);
  REQUIRE (result2==true);
  REQUIRE (distance2==Approx(4.0f));
}

TEST_CASE ("Kon-Destruktor","[shape]")
{
    Color red{255, 0, 0};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    Sphere* s1 = new Sphere{red, "sphere0", position, 1.2f}; //hier wird der Benutzerkonstruktor aufgerufen und das Objekt wird angelegt
    Shape* s2 = new Sphere{red, "sphere1", position, 1.2f};
    s1->print(std::cout); //hier wird das Objekt auf der Konsole geprintet 
    s2->print(std::cout);
    delete s1; //hier wird das Objekt gelöscht indem der Destructor aufgerufen wird 
    delete s2; //dynamische Speicherverwaltung durch new und delete 
}

TEST_CASE ("intersect_ray_box", "[intersect]")
{
    Box box1 {{3.0f, -1.5f, -1.5f}, {7.0f, 1.5f, 1.5f}};
    Ray ray1 {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}};
    float distance1 = 0.0f; 
    REQUIRE (box1.intersect(ray1, distance1) == true);

    Box box2 {{0.0f, 0.0f, 0.0f}, {5.0f, 5.0f, 5.0f}};
    Ray ray2 {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{-1.0f, -2.0f, 0.0f}};
    float distance2 = 1.0f; 
    REQUIRE (box2.intersect(ray2, distance2) == false); 

    Box box3 {{0.0f, 0.0f, 0.0f}, {5.0f, 5.0f, 5.0f}};
    Ray ray3 {glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}};
    float distance3 = 0.0f; 
    REQUIRE (box3.intersect(ray3, distance3) == true); 
    //////Hier nochmal nachschauen und prüfen warum das falsch wäre
} 


int main(int argc, char *argv[])
{

  //Aufgabe 5.5 

/*   Sphere sphere1;
  std::cout << sphere1 << "\n";

  Sphere sphere2 {{0.8f,0.3f,0.5f}, "Kugel 2", {0.5f,0.3f,1.0f}, 8.0f};
  std::cout << sphere2 << "\n"; 

  Box box1; 
  std::cout << box1 << "\n"; 

  Box box2 {{0.8f,0.3f,0.5f}, "Box 2", {0.5f,0.3f,1.0f}, {5.0f,3.0f,10.0f}}; 
  std::cout << box2 << "\n"; */


  return Catch::Session().run(argc, argv);
}
