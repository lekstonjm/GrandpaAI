#ifndef _ImplicationCNFTransformer_HPP_
#define _ImplicationCNFTransformer_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct ImplicationCNFTransformer {
    ImplicationCNFTransformer();
    void Transform(Ref<Formula> &);
private:
    void TransformStandard(Ref<Formula> &);
    void TransformPredicate(Ref<Formula> &);
    void TransformFunction(Ref<Function> &);
    void TransformEquality(Ref<Formula> &);
    void TransformImplication(Ref<Formula> &);
    void TransformNegation(Ref<Formula> &);
    void TransformConnective(Ref<Formula> &);
    void TransformQuantifier(Ref<Formula> &);
    typedef void (ImplicationCNFTransformer::*TransformMethod)(Ref<Formula> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
};


#endif