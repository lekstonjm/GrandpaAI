#include <iostream>
#include "logic_node.hpp"

int main() {
  try {
    Ref<Prototype> PI(new Prototype("P",1));
    Ref<Prototype> QI(new Prototype("Q",2));

    Ref<Constant> C(new Constant("C"));
    Ref<Predicate> P(new Predicate(PI));
    P->terms.push_back(C.cast<Term>());

    Ref<Predicate> Q(new Predicate(QI));
    Ref<Variable> X(new Variable("X"));
    Ref<Variable> Y(new Variable("Y"));
    Q->terms.push_back(X.cast<Term>());
    Q->terms.push_back(Y.cast<Term>());

    Ref<Implication> I(new Implication());
    I->left.assign<Predicate>(Q);
    I->right.assign<Predicate>(P);

    Ref<Universal> UX(new Universal());
    UX->variables.push_back(X);
    UX->variables.push_back(Y);
    UX->formula.assign<Implication>(I);
    std::cout << UX->toString() << std::endl;
  } catch(...) {
    std::cout<<"Exception occured" << std::endl;
  }
}
