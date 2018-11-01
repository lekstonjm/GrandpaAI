#include "connective_cnf_transformer.hpp"
#include <algorithm>


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
    if (formula.is<Conjunction>()) {
      Fusion(input, formula);
      Transform(input);
      break;
    } else {
      Transform(formula);
    }
  }
}

void ConnectiveCNFTransformer::TransformDisjunction(Ref<Formula> &input) {
  for (auto& formula:input.as<Disjunction>()->formulas) {
    if (formula.is<Disjunction>()) {
      Fusion(input,formula);
      Transform(input);
      break;
    } else if(formula.is<Conjunction>()) {
      DistributeDisjunction(input, formula);
      Transform(input);
      break;
    } else {
      Transform(formula);
    }
  }
}
// ( A ^ ( B ^ C ) ) => ( A ^ B  ^ C )
// ( A ^ B ^ ( C ^ D ) ^ E ) => ( A ^ B ^ E ^ C ^ D )
void ConnectiveCNFTransformer::Fusion(Ref<Formula> &input, Ref<Formula> &connective) {
  input.as<Connective>()->formulas.erase(std::remove_if(
    input.as<Connective>()->formulas.begin(),input.as<Connective>()->formulas.end()
    ,[&](Ref<Formula> &formula) { return formula == connective; } ));
  for (auto &formula:connective.as<Connective>()->formulas) {
    input.as<Connective>()->formulas.push_back(formula);
  }
}
// (A v (B ^ C) ) => (  ( A v B ) ^ ( A v C ) )
// ( A ^ B) v ( C ^ D ) => ( (A ^ B ) v C ) ^ ( A ^ B ) v D ) => ( A v C ) ^ (B v C ) ^ ( A v D ) ^ ( B v D ) 
// ( A v B v ( C ^ D ) ) => ( A v ( ( B v C ) ^ (B v D ) ) ) = > ( A v B v C ) ^ ( A v B v D ) 
void ConnectiveCNFTransformer::DistributeDisjunction(Ref<Formula> &input, Ref<Formula> &into_conjunction) {
  Ref<Conjunction> conjunction_result(new Conjunction());
  for (auto& conjunction_formula : into_conjunction.as<Connective>()->formulas) {
    Ref<Formula> disjunction_result(new Disjunction());
    disjunction_result.as<Disjunction>()->formulas.push_back(conjunction_formula);
    for (auto& disjunction_formula : input.as<Disjunction>()->formulas) {
      if (! (disjunction_formula == into_conjunction) ) {
        disjunction_result.as<Disjunction>()->formulas.push_back(disjunction_formula);
      }
    }
    conjunction_result->formulas.push_back(disjunction_result);
  }
  input.assign<Conjunction>(conjunction_result);
}