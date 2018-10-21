#include <iostream>
#include "node.hpp"

int main() {
  Ref<Constant> C(new Constant("C"));
  Ref<Predicate> P(new Predicate("P"));
  P->terms.push_back(C.cast<Term>());
  
  Ref<Predicate> Q(new Predicate("Q"));
  Ref<Variable> X(new Variable("X"));
  Q->terms.push_back(X.cast<Term>());
  
  Ref<Implication> I(new Implication());
  I->head.assign<Predicate>(Q);
  I->body.assign<Predicate>(P);

  Ref<UniversalQuantifier> UX(new UniversalQuantifier());
  UX->variable = X;
  UX->formula.assign<Implication>(I);

  std::cout << UX->toString() << std::endl;
}
