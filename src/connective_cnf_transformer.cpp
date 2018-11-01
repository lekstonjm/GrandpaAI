#include "connective_cnf_transformer.hpp"


ConnectiveCNFTransformer::ConnectiveCNFTransformer() {
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Predicate))
      , &ConnectiveCNFTransformer::TransformStandard));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Equality))
      , &ConnectiveCNFTransformer::TransformStandard));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Negation))
      , &ConnectiveCNFTransformer::TransformNegation));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Implication))
      , &ConnectiveCNFTransformer::TransformImplication));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Disjunction))
      , &ConnectiveCNFTransformer::TransformDisjunction));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Conjunction))
      , &ConnectiveCNFTransformer::TransformConjunction));
  transform_method_map.insert(
      std::make_pair(std::type_index(typeid(Existantial))
      , &ConnectiveCNFTransformer::TransformQuantifier));
  transform_method_map.insert(std::make_pair(
      std::type_index(typeid(Universal))
      , &ConnectiveCNFTransformer::TransformQuantifier));
}

void ConnectiveCNFTransformer::Transform(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  TransformMethod method = transform_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input);
}

void ConnectiveCNFTransformer::TransformStandard(Ref<Formula> &input) {
}

void ConnectiveCNFTransformer::TransformNegation(Ref<Formula> &input) {
  Transform(input.as<Negation>()->formula);
}

void ConnectiveCNFTransformer::TransformImplication(Ref<Formula> &input) {
  Transform(input.as<Implication>()->right);
  Transform(input.as<Implication>()->left);
}

void ConnectiveCNFTransformer::TransformQuantifier(Ref<Formula> &input) {
  Transform(input.as<Quantifier>()->formula);
}

void ConnectiveCNFTransformer::TransformConjunction(Ref<Formula> &input) {
  for (auto& formula:input.as<Conjunction>()->formulas) {
    Transform(formula);
  }
}

void ConnectiveCNFTransformer::TransformDisjunction(Ref<Formula> &input) {
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
