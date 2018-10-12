#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include "exception.hpp"
#include "reference.hpp"
#include "node.hpp"

struct Inverter {
  typedef void (Inverter::*InvertMethod)(const Ref<Node> &input, Ref<Node> &output);
  std::unordered_map<std::type_index, InvertMethod> invert_method_map;
  Inverter();
  void Invert(const Ref<Node> &, Ref<Node> &);
  void InvertConstant(const Ref<Node> &, Ref<Node> &);
  void InvertNot(const Ref<Node> &, Ref<Node> &);
  void InvertDisjunction(const Ref<Node> &, Ref<Node> &);
};

Inverter::Inverter() {
  invert_method_map.insert(std::make_pair(std::type_index(typeid(Constant)),&Inverter::InvertConstant));
  invert_method_map.insert(std::make_pair(std::type_index(typeid(Disjunction)),&Inverter::InvertDisjunction));
}
void Inverter::Invert(const Ref<Node> &input, Ref<Node> &output) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  InvertMethod method = invert_method_map[node_type_index];
  (this->*method)(input, output);
}

void Inverter::InvertConstant(const Ref<Node> &input, Ref<Node> &output) {
    const Constant &constant = dynamic_cast<const Constant &>(*input);
    Ref<Negation> negation(new Negation());
    negation->node = constant;
    output = negation;
}

void Inverter::InvertNegation(const Ref<Node> &input, Ref<Node> &output) {
  const Node &node = *input;
  const Negation &negation = dynamic_cast<const Negation &>(node);

}

void Inverter::InvertDisjunction(const Ref<Node> &input, Ref<Node> &output) {
  const Node &node = *input;
  const Disjunction &disjunction = dynamic_cast<const Disjunction &>(node);
  Conjunction *conjunction = new Conjunction();
  output = Ref<Node>(conjunction);
  for (auto &node : disjunction.nodes) {
    Ref<Node> inv_node;
    Invert(node, inv_node);
    conjunction->nodes.push_back(inv_node);
  }
}

int main(int argc, char *argv[])
{
  if (true) {
    Constant *a = new Constant("A");
    Ref<Node> A(a);
    Ref<Node> B(new Constant("B"));
    Ref<Node> C(new Constant("C"));
    Disjunction *d1 = new Disjunction();
    Ref<Node> D1(d1);
    d1->nodes.push_back(A);
    d1->nodes.push_back(B);
    d1->nodes.push_back(C);
    std::cout << A.counter->count<< std::endl;
    std::cout << "ok" << std::endl;
    std::cout << D1->toString() << std::endl;
    Inverter inverter;
    Ref<Node> inv_d1;
    inverter.Invert(D1,inv_d1);
    std::cout << inv_d1->toString() << std::endl;
  }
}
