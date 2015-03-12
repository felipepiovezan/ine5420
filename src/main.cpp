#include <iostream>
#include "GObject.h"

int main(int argc, char **argv) {
  GObject test;
  test.name = "Carlos Bonetti";
  std::cout << test.name << " " << test.test() << std::endl;
  std::cout << "Call Qt or GTK+ here! Yet to decide..." << std::endl;

  return 0;
}
