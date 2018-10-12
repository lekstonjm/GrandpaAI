#include <iostream>
#include "exception.hpp"
#include "reference.hpp"
#include "node.hpp"
#include "inverter.hpp"

int main(int argc, char *argv[])
{
    Ref<Node> A(new Constant("A"));
    Ref<Node> B(new Constant("B"));
    Ref<Node> C(new Constant("C"));
    Disjunction *d1 = new Disjunction();
    d1->nodes.push_back(A);
    d1->nodes.push_back(B);
    d1->nodes.push_back(C);
    Ref<Node> D1(d1);
    Inverter inverter;
    Ref<Node> inv_d1;
    inverter.Invert(D1,inv_d1);
    std::cout <<"ok" <<  inv_d1->toString() << std::endl;
}
