#include <iostream>
#include "logic_node.hpp"

int main() {
  Ref<Constant> C(new Constant("C"));
  Ref<Predicate> P(new Predicate("P"));
  P->terms.push_back(C.cast<Term>());

  Ref<Predicate> Q(new Predicate("Q"));
  Ref<Variable> X(new Variable("X"));
  Q->terms.push_back(X.cast<Term>());

  Ref<Implication> I(new Implication());
  I->left.assign<Predicate>(Q);
  I->right.assign<Predicate>(P);

  Ref<Universal> UX(new Universal());
  UX->variable = X;
  UX->formula.assign<Implication>(I);

  std::cout << UX->toString() << std::endl;
}
