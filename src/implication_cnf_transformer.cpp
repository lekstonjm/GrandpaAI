#include "implication_cnf_transformer.hpp"
#include <typeinfo>
#include <iostream>

ImplicationCNFTransformer::ImplicationCNFTransformer() {
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Predicate))
        , &ImplicationCNFTransformer::TransformStandard));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Equality))
        , &ImplicationCNFTransformer::TransformStandard));        
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Negation))        
        , &ImplicationCNFTransformer::TransformNegation));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Implication))
        , &ImplicationCNFTransformer::TransformImplication));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Disjunction))
        , &ImplicationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Conjunction))
        , &ImplicationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Existantial))
        , &ImplicationCNFTransformer::TransformQuantifier));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Universal))
        , &ImplicationCNFTransformer::TransformQuantifier));
}

void ImplicationCNFTransformer::Transform(Ref<Formula> &input) {
  std::type_index node_type_index = std::type_index(typeid(*input));
  TransformMethod method = transform_method_map[node_type_index];
  if (method == NULL) {
    NotImplementedException::Throw();
  }
  (this->*method)(input);
}

void ImplicationCNFTransformer::TransformStandard(Ref<Formula> &input) {
}

void ImplicationCNFTransformer::TransformImplication(Ref<Formula> &input) {
    Ref<Implication> implication;
    implication.assign<Formula>(input);
    Transform(implication->left);
    Transform(implication->right); 

    Ref<Disjunction> disjunction(new Disjunction());
    Ref<Negation> negation(new Negation());
    negation->formula = implication->left;
    disjunction->formulas.push_back(negation.cast<Formula>());
    disjunction->formulas.push_back(implication->right);
    input.assign<Disjunction>(disjunction);
}

void ImplicationCNFTransformer::TransformNegation(Ref<Formula> &input) {
    Ref<Negation> negation;
    negation.assign<Formula>(input);
    Transform(negation->formula);
}

void ImplicationCNFTransformer::TransformConnective(Ref<Formula> &input) {
    Ref<Connective> connective;
    connective.assign<Formula>(input);
    for (auto& formula:connective->formulas) {
        Transform(formula);
    }
}

void ImplicationCNFTransformer::TransformQuantifier(Ref<Formula> &input) {
    Ref<Quantifier> quantifier;
    quantifier.assign<Formula>(input);
    Transform(quantifier->formula);
}