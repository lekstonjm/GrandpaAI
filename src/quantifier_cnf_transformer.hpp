#ifndef _QuantifierCNFTransformer_HPP_
#define _QuantifierCNFTransformer_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct QuantifierCNFTransformer {
    typedef void (QuantifierCNFTransformer::*TransformMethod)(Ref<Formula> &, Ref<Universal> &, Ref<Existantial> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
    QuantifierCNFTransformer();
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