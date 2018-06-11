#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "box.hpp"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
