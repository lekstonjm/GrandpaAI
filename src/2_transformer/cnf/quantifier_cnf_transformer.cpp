#include "quantifier_cnf_transformer.hpp"

QuantifierCNFTransformer::QuantifierCNFTransformer(){
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Predicate))
        , &QuantifierCNFTransformer::TransformStandard));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Equality))
        , &QuantifierCNFTransformer::TransformStandard));        
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Negation))        
        , &QuantifierCNFTransformer::TransformNegation));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Implication))
        , &QuantifierCNFTransformer::TransformImplication));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Disjunction))
        , &QuantifierCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Conjunction))
        , &QuantifierCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Existantial))
        , &QuantifierCNFTransformer::TransformExistantial));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Universal))
        , &QuantifierCNFTransformer::TransformUniversal));
}

void QuantifierCNFTransformer::Transform(Ref<Formula> &input) {
    Ref<Universal> root_universal(new Universal());
    Ref<Existantial> root_existantial(new Existantial());
    Transform(input, root_universal, root_existantial);
    root_universal->formula.assign<Existantial>(root_existantial);
    root_existantial->formula = input;
    input.assign<Universal>(root_universal);    
}

void QuantifierCNFTransformer::Transform(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    std::type_index node_type_index = std::type_index(typeid(*input));
    TransformMethod method = transform_method_map[node_type_index];
    if (method == NULL) {
        NotImplementedException::Throw();
    }
    (this->*method)(input, root_universal, root_existantial);
}

void QuantifierCNFTransformer::TransformStandard(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {

}

void QuantifierCNFTransformer::TransformImplication(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Implication> implication;
    implication.assign<Formula>(input);
    Transform(implication->left, root_universal, root_existantial);
    Transform(implication->right, root_universal, root_existantial);
}

void QuantifierCNFTransformer::TransformNegation(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Negation> negation;
    negation.assign<Formula>(input);
    Transform(negation->formula, root_universal, root_existantial);
}

void QuantifierCNFTransformer::TransformConnective(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Connective> connective;
    connective.assign<Formula>(input);
    for (auto &formula:connective->formulas) {
        Transform(formula, root_universal, root_existantial);
    }
}
void QuantifierCNFTransformer::TransformUniversal(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Universal> universal;
    universal.assign<Formula>(input);
    for (auto &variable:universal->variables) {
        root_universal->variables.push_back(variable);
    }
    input = universal->formula;
    Transform(input, root_universal, root_existantial);
}

void QuantifierCNFTransformer::TransformExistantial(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Existantial> existantial;
    existantial.assign<Formula>(input);
    for (auto &variable:existantial->variables) {
        root_existantial->variables.push_back(variable);
    }
    input = existantial->formula;
    Transform(input, root_universal, root_existantial);
}
