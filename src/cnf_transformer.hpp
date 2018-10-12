#ifndef _CNFTransformer_HPP_
#define _CNFTransformer_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"
// CNF Stand for Conjonctive Normal Form
// A CNF formula contains only
// - Implication are writen to their conjunction equivalency
// - Negation are at the nearest term position using de morgan law
// - Quantifier are expanded using skolemization
// - Conjunction of disjunction
struct CNFTransformer {
  typedef void (CNFTransformer::*TransformMethod)(const Ref<Formula> &input, Ref<Formula> &output);
  std::unordered_map<std::type_index, TransformMethod> transform_method_map;
  void Transform(const Ref<Formula> &, Ref<Formula> &);
  void TransformImplication(const Ref<Formula> &, Ref<Formula> &);
};

#endif
