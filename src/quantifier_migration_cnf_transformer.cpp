#include "quantifier_migration_cnf_transformer.hpp"

QuantifierMigrationCNFTransformer::QuantifierMigrationCNFTransformer(){
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Predicate))
        , &QuantifierMigrationCNFTransformer::TransformStandard));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Equality))
        , &QuantifierMigrationCNFTransformer::TransformStandard));        
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Negation))        
        , &QuantifierMigrationCNFTransformer::TransformNegation));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Implication))
        , &QuantifierMigrationCNFTransformer::TransformImplication));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Disjunction))
        , &QuantifierMigrationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Conjunction))
        , &QuantifierMigrationCNFTransformer::TransformConnective));
    transform_method_map.insert(
        std::make_pair(std::type_index(typeid(Existantial))
        , &QuantifierMigrationCNFTransformer::TransformExistantial));
    transform_method_map.insert(std::make_pair(
        std::type_index(typeid(Universal))
        , &QuantifierMigrationCNFTransformer::TransformUniversal));
}

void QuantifierMigrationCNFTransformer::Transform(Ref<Formula> &input) {
    Ref<Universal> root_universal(new Universal());
    Ref<Existantial> root_existantial(new Existantial());
    Transform(input, root_universal, root_existantial);
    root_universal->formula.assign<Existantial>(root_existantial);
    root_existantial->formula = input;
    input.assign<Universal>(root_universal);    
}

void QuantifierMigrationCNFTransformer::Transform(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    std::type_index node_type_index = std::type_index(typeid(*input));
    TransformMethod method = transform_method_map[node_type_index];
    if (method == NULL) {
        NotImplementedException::Throw();
    }
    (this->*method)(input, root_universal, root_existantial);
}

void QuantifierMigrationCNFTransformer::TransformStandard(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {

}

void QuantifierMigrationCNFTransformer::TransformImplication(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Implication> implication;
    implication.assign<Formula>(input);
    Transform(implication->left, root_universal, root_existantial);
    Transform(implication->right, root_universal, root_existantial);
}

void QuantifierMigrationCNFTransformer::TransformNegation(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Negation> negation;
    negation.assign<Formula>(input);
    Transform(negation->formula, root_universal, root_existantial);
}

void QuantifierMigrationCNFTransformer::TransformConnective(Ref<Formula> &input
    , Ref<Universal> &root_universal
    , Ref<Existantial> &root_existantial) {
    Ref<Connective> connective;
    connective.assign<Formula>(input);
    for (auto &formula:connective->formulas) {
        Transform(formula, root_universal, root_existantial);
    }
}
void QuantifierMigrationCNFTransformer::TransformUniversal(Ref<Formula> &input
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

void QuantifierMigrationCNFTransformer::TransformExistantial(Ref<Formula> &input
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
