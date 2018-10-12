#include "reference.hpp"
#include <iostream>

struct Object {
  virtual void virtMethod() {}
};
struct Derive : virtual Object {
  virtual void virtMethod() {}
};

int main(int argc, char *argv[]) {
  Ref<Object> obj;
  Ref<Derive> derive(new Derive());
  obj.assign<Derive>(derive);
  std::cout<<"ok"<<std::endl;
}
