 #ifndef _INVERTER_HPP_
 #define _INVERTER_HPP_

 #include <unordered_map>
 #include <typeindex>
#include "reference.hpp"
#include "node.hpp"

struct Inverter {
  typedef void (Inverter::*InvertMethod)(const Ref<Node> &input, Ref<Node> &output);
  std::unordered_map<std::type_index, InvertMethod> invert_method_map;
  Inverter();
  void Invert(const Ref<Node> &, Ref<Node> &);
  void InvertConstant(const Ref<Node> &, Ref<Node> &);
  void InvertNegation(const Ref<Node> &, Ref<Node> &);
  void InvertDisjunction(const Ref<Node> &, Ref<Node> &);
};

#endif
