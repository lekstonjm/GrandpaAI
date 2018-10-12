#include "inverter.hpp"
#include <typeinfo>

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
    negation->node = input;
    output.assign<Negation>(negation);
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
