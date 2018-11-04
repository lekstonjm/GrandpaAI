#ifndef _NegationCNFTransformer_HPP_
#define _NegationCNFTransformer_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct NegationCNFTransformer {
    NegationCNFTransformer();
    void Transform(Ref<Formula> &input);
private:
    void TransformStandard(Ref<Formula> &input);
    void TransformNegation(Ref<Formula> &input);
    void TransformImplication(Ref<Formula> &input);
    void TransformConnective(Ref<Formula> &input);
    void TransformQuantifier(Ref<Formula> &input);
    typedef void (NegationCNFTransformer::*TransformMethod)(Ref<Formula> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
};

#endif