#include "disjunction_cnf_transformer.hpp"


DisjunctionCNFTransformer::DisjunctionCNFTransformer() {
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Predicate))
      , &DisjunctionCNFTransformer::TransformStandard));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Equality))
      , &DisjunctionCNFTransformer::TransformStandard));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Negation))
      , &DisjunctionCNFTransformer::TransformNegation));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Implication))
      , &DisjunctionCNFTransformer::TransformImplication));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Disjunction))
      , &DisjunctionCNFTransformer::TransformDisjunction));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Conjunction))
      , &DisjunctionCNFTransformer::TransformConjunction));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Existantial))
      , &DisjunctionCNFTransformer::TransformQuantifier));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Universal))
      , &DisjunctionCNFTransformer::TransformQuantifier));
}

void DisjunctionCNFTransformer::Transform(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  TransformMethod method = transform_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input);
}

void DisjunctionCNFTransformer::TransformStandard(Ref<Formula> &input) {
}

void DisjunctionCNFTransformer::TransformNegation(Ref<Formula> &input) {
  Transform(input.as<Negation>()->formula);
}

void DisjunctionCNFTransformer::TransformImplication(Ref<Formula> &input) {
  Transform(input.as<Implication>()->right);
  Transform(input.as<Implication>()->left);
}

void DisjunctionCNFTransformer::TransformQuantifier(Ref<Formula> &input) {
  Transform(input.as<Quantifier>()->formula);
}

void DisjunctionCNFTransformer::TransformConjunction(Ref<Formula> &input) {
  for (auto& formula:input.as<Conjunction>()->formulas) {
    Transform(formula);
  }
}

void DisjunctionCNFTransformer::TransformDisjunction(Ref<Formula> &input) {
  NotImplementedException::Throw();

  Ref<Conjunction> c;
  Ref<Disjunction> d;
  d.assign<Formula> (input);
  for (auto& formula:d.as<Disjunction>()->formulas) {
    if(formula.is<Conjunction>()) {
      c.assign<Formula>(formula);
      break;
    }
  }
  if (!c.isNull()) {
    Ref<Formula> r_c(new Conjunction());
    for (auto& formula_d:d.as<Disjunction>()->formulas) {
      Ref<Formula> r_d(new Disjunction());
      for (auto& formula_c:c.as<Conjunction>()->formulas) {
        r_d.as<Disjunction>()->formulas.push_back(formula_d);
        r_d.as<Disjunction>()->formulas.push_back(formula_c);
      }
      r_c.as<Conjunction>()->formulas.push_back(r_d);
    }
  }
}
