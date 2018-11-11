#include "negater.hpp"
#include <typeinfo>
#include <iostream>

Negater::Negater() {
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Predicate))
    ,&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Equality))
    ,&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Negation))
    ,&Negater::NegateNegation));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Disjunction))
    ,&Negater::NegateDisjunction));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Conjunction))
    ,&Negater::NegateConjunction));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Existantial))
    ,&Negater::NegateExistantial));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Universal))
    ,&Negater::NegateUniversal));
  negater_method_map.insert(std::make_pair(
    std::type_index(typeid(Implication))
    ,&Negater::NegateImplication));
}

void Negater::Negate(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  NegateMethod method = negater_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input);
}

void Negater::NegateStandard(Ref<Formula> &input) {
  Ref<Negation> negation(new Negation());
  negation->formula.assign<Formula>(input);
  input.assign<Negation>(negation);
}

void Negater::NegateNegation(Ref<Formula> &input) {
  Ref<Negation> negation;
  negation.assign<Formula>(input);
  input = negation->formula;
}

void Negater::NegateDisjunction(Ref<Formula> &input) {
  Ref<Disjunction> disjunction;
  disjunction.assign<Formula>(input);

  Ref<Conjunction> conjunction(new Conjunction());
  for (auto &formula : disjunction->formulas) {
    Negate(formula);
    conjunction->formulas.push_back(formula);
  }
  input.assign<Conjunction>(conjunction);
}

void Negater::NegateConjunction(Ref<Formula> &input) {
  Ref<Conjunction> conjunction;
  conjunction.assign<Formula>(input);

  Ref<Disjunction> disjunction(new Disjunction());
  for (auto &formula : conjunction->formulas) {
    Negate(formula);
    disjunction->formulas.push_back(formula);
  }
  input.assign<Disjunction>(disjunction);
}

void Negater::NegateExistantial(Ref<Formula> &input) {
  Ref<Existantial> existantial;
  existantial.assign<Formula>(input);
  Negate(existantial->formula);
  Ref<Universal> universal(new Universal);
  universal->variables = existantial->variables;
  universal->formula = existantial->formula;
  input.assign<Universal>(universal);
}

void Negater::NegateUniversal(Ref<Formula> &input) {
  Ref<Universal> universal;
  universal.assign<Formula>(input);
  Negate(universal->formula);
  Ref<Existantial> existantial(new Existantial());
  existantial->variables = universal->variables;
  existantial->formula = universal->formula;
  input.assign<Existantial>(existantial);
}

void Negater::NegateImplication(Ref<Formula> &input) {
  Ref<Implication> implication;
  implication.assign<Formula>(input);
  Ref<Conjunction> conjunction(new Conjunction());
  conjunction->formulas.push_back(implication->left);
  Negate(implication->right);
  conjunction->formulas.push_back(implication->right);
  input.assign<Conjunction>(conjunction);
}