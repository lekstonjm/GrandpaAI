#ifndef _CNFTransformer_HPP_
#define _CNFTransformer_HPP_
#include "reference.hpp"
// CNF Stand for Conjonctive Normal Form
// A CNF formula contains only 
// - disjunction of conjuction 
// - and negation are at the nearest term position, 
// - implication are writen to their conjunction equivalency
// ( ( P(A) v P(B) ) => (Q(A) ^ Q(B) ) ^ (Q(A) v Q(B) ) ) <=>  
struct CNFTransformer {
    void Transform(const Ref<Formula> &, Ref<Formula> &);
};

#endif