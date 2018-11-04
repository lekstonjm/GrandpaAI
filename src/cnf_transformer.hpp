#ifndef _CNFTransformer_HPP_
#define _CNFTransformer_HPP_

#include "reference.hpp"
#include "logic_node.hpp"
#include "implication_cnf_transformer.hpp"
#include "negation_cnf_transformer.hpp"
#include "quantifier_cnf_transformer.hpp"
#include "connective_cnf_transformer.hpp"

// CNF Stand for Conjonctive Normal Form
// A CNF formula contains only
// - Implication are writen to their conjunction equivalency
// - Negation are at the nearest term position using de morgan law
// - Quantifier are expanded using skolemization
// - Conjunction of disjunction
struct CNFTransformer {
  void Transform(Ref<Formula> &);
private:
  ImplicationCNFTransformer implication_transformer;
  NegationCNFTransformer negation_transformer;
  QuantifierCNFTransformer quantifier_transformer;
  ConnectiveCNFTransformer connective_transformer;
};

#endif
