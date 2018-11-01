#ifndef _DISJUNCTION_CNF_TRANSFORMER_HPP_
#define _DISJUNCTION_CNF_TRANSFORMER_HPP_
#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct ConnectiveCNFTransformer {
    typedef void (ConnectiveCNFTransformer::*TransformMethod)(Ref<Formula> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
    ConnectiveCNFTransformer();
    void Transform(Ref<Formula> &);
    void TransformStandard(Ref<Formula> &input);
    void TransformNegation(Ref<Formula> &input);
    void TransformImplication(Ref<Formula> &input);
    void TransformConjunction(Ref<Formula> &input);
    void TransformDisjunction(Ref<Formula> &input);
    void TransformQuantifier(Ref<Formula> &input);
};

#endif
