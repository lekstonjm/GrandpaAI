#include "negation_cnf_transformer.hpp"
#include "negater.hpp"
#include <iostream>

NegationCNFTransformer::NegationCNFTransformer() {
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Predicate))
        , &NegationCNFTransformer::TransformStandard));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Equality))
        , &NegationCNFTransformer::TransformStandard));        
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Negation))        
        , &NegationCNFTransformer::TransformNegation));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Implication))
        , &NegationCNFTransformer::TransformImplication));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Disjunction))
        , &NegationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Conjunction))
        , &NegationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Existantial))
        , &NegationCNFTransformer::TransformQuantifier));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Universal))
        , &NegationCNFTransformer::TransformQuantifier));
}

void NegationCNFTransformer::Transform(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  TransformMethod method = transform_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  } 
  (this->*method)(input);
}

void NegationCNFTransformer::TransformStandard(Ref<Formula> &input) {    
}

void NegationCNFTransformer::TransformNegation(Ref<Formula> &input) {
    Ref<Negation> negation;
    negation.assign<Formula>(input);
    Negater negater;
    negater.Negate(negation->formula);
    if (!negation->formula.is<Negation>()) {
        Transform(negation->formula);
    }
    input = negation->formula;
}

void NegationCNFTransformer::TransformImplication(Ref<Formula> &input) {
    Ref<Implication> implication;
    implication.assign<Formula>(input);
    Transform(implication->left);
    Transform(implication->right);
}


void NegationCNFTransformer::TransformConnective(Ref<Formula> &input) {
    Ref<Connective> connective;
    connective.assign<Formula>(input);
    for (auto &formula:connective->formulas) {
        Transform(formula);
    }
}

void NegationCNFTransformer::TransformQuantifier(Ref<Formula> &input) {
    Ref<Quantifier> quantifier;
    quantifier.assign<Formula>(input);
    Transform(quantifier->formula);

}
