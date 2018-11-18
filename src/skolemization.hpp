#ifndef _Skolemization_HPP_
#define _Skolemization_HPP_

#include "reference.hpp"
#include "logic_node.hpp"
#include <unordered_map>
#include <typeindex>
#include <stack>

struct Skolemization {
    Skolemization();
    void Transform(Ref<Formula>&);
private:
    void TransformPredicate(Ref<Formula> &);
    void TransformEquality(Ref<Formula> &);
    void TransformNegation(Ref<Formula> &);
    void TransformImplication(Ref<Formula> &);
    void TransformConnective(Ref<Formula> &);
    void TransformExistantial(Ref<Formula> &);
    void TransformUniversal(Ref<Formula> &);
    typedef void (Skolemization::*TransformMethod)(Ref<Formula> &);
    std::unordered_map<std::type_index, TransformMethod> transform_method_map;
    std::unordered_map<Ref<Variable>,Ref<Function> > skolem_functions;
    std::vector<Ref<Universal>> universal_stack;        
};

#endif