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
  Ref<Derive> derive2;
  derive2.assign<Object>(obj);
  Ref<Derive> derive3;
  derive3 = obj.cast<Derive>();
  std::cout<<"ok"<<std::endl;
}
