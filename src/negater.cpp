#include "negater.hpp"
#include <typeinfo>
#include <iostream>

Negater::Negater() {
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Variable)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Constant)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Function)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Predicate)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Equality)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Implication)),&Negater::NegateStandard));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Negation)),&Negater::NegateNegation));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Disjunction)),&Negater::NegateDisjunction));
  negater_method_map.insert(std::make_pair(std::type_index(typeid(Conjunction)),&Negater::NegateConjunction));
}

void Negater::Negate(const Ref<Formula> &input, Ref<Formula> &output) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  NegateMethod method = negater_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input, output);
}

void Negater::NegateStandard(const Ref<Formula> &input, Ref<Formula> &output) {
    Ref<Negation> negation(new Negation());
    negation->formula.assign<Formula>(input);
    output.assign<Negation>(negation);

  }
void Negater::NegateNegation(const Ref<Formula> &input, Ref<Formula> &output) {
  Ref<Negation> negation;
  negation.assign<Formula>(input);
  output = negation->formula;
}

void Negater::NegateDisjunction(const Ref<Formula> &input, Ref<Formula> &output) {
  Ref<Disjunction> disjunction;
  disjunction.assign<Formula>(input);
  Ref<Conjunction> conjunction(new Conjunction());
  for (auto &formula : disjunction->formulas) {
    Ref<Formula> negate_formula;
    Negate(formula, negate_formula);
    conjunction->formulas.push_back(negate_formula);
  }
  output.assign<Conjunction>(conjunction);
}

void Negater::NegateConjunction(const Ref<Formula> &input, Ref<Formula> &output) {
  Ref<Conjunction> conjunction;
  conjunction.assign<Formula>(input);
  Ref<Disjunction> disjunction(new Disjunction());
  for (auto &formula : conjunction->formulas) {
    Ref<Formula> negate_formula;
    Negate(formula, negate_formula);
    disjunction->formulas.push_back(negate_formula);
  }
  output.assign<Disjunction>(disjunction);
}
