#include "skolemization.hpp"

Skolemization::Skolemization() {
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Predicate))
        , &Skolemization::TransformPredicate));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Equality))
        , &Skolemization::TransformEquality));        
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Negation))        
        , &Skolemization::TransformNegation));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Implication))
        , &Skolemization::TransformImplication));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Disjunction))
        , &Skolemization::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Conjunction))
        , &Skolemization::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Existantial))
        , &Skolemization::TransformExistantial));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Universal))
        , &Skolemization::TransformUniversal));
}

void Skolemization::Transform(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  TransformMethod method = transform_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input);
}

void Skolemization::TransformPredicate(Ref<Formula> &formula){
    for(auto &item:formula.as<Predicate>()->terms) {
        if (item.is<Variable>()&&skolem_functions.count(item.cast<Variable>()))  {
            item.assign<Function>(skolem_functions[item.cast<Variable>()]);
        } 
    }    
}

void Skolemization::TransformEquality(Ref<Formula> &formula){
    if (formula.as<Equality>()->left.is<Variable>()&&skolem_functions.count(formula.as<Equality>()->left.cast<Variable>())) {
        formula.as<Equality>()->left.assign<Function>(skolem_functions[formula.as<Equality>()->left.cast<Variable>()]);
    } 
    if (formula.as<Equality>()->right.is<Variable>()&&skolem_functions.count(formula.as<Equality>()->right.cast<Variable>())) {
        formula.as<Equality>()->right.assign<Function>(skolem_functions[formula.as<Equality>()->right.cast<Variable>()]);
    } 
}

void Skolemization::TransformImplication(Ref<Formula> &formula){
    Transform(formula.as<Implication>()->left);
    Transform(formula.as<Implication>()->right);
}

void Skolemization::TransformNegation(Ref<Formula> &formula){
    Transform(formula.as<Negation>()->formula);
}

void Skolemization::TransformConnective(Ref<Formula> &formula){
    for (auto &item:formula.as<Connective>()->formulas) {
        Transform(item);
    }
}

void Skolemization::TransformExistantial(Ref<Formula> &formula){
    for(auto &existantial_variable:formula.as<Existantial>()->variables) {
        Ref<Function> skolem_function(new Function(existantial_variable->name));
        for (auto &universal:universal_stack) {
            for (auto &universal_variable:universal->variables) {
                skolem_function->terms.push_back(universal_variable.cast<Term>());
            }
        }
        skolem_functions[existantial_variable] = skolem_function;        
    }
    Transform(formula.as<Existantial>()->formula);
    formula = formula.as<Existantial>()->formula;
}

void Skolemization::TransformUniversal(Ref<Formula> &formula){
    universal_stack.push_back(formula.cast<Universal>());
    Transform(universal_stack.back()->formula);
    universal_stack.pop_back();    
}
