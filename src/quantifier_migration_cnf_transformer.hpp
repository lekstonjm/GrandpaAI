#ifndef _QuantifierMigrationCNFTransformer_HPP_
#define _QuantifierMigrationCNFTransformer_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct QuantifierMigrationCNFTransformer {
    typedef void (QuantifierMigrationCNFTransformer::*TransformMethod)(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
    QuantifierMigrationCNFTransformer();
    void Transform(Ref<Formula> &);
    void Transform(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformStandard(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformImplication(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformNegation(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformConnective(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformUniversal(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    void TransformExistantial(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
};

#endif