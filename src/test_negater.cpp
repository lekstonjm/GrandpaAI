#include <iostream>
#include "exception.hpp"
#include "reference.hpp"
#include "node.hpp"
#include "negater.hpp"

int main(int argc, char *argv[])
{
  try {
    Ref<Term> A(new Constant("A"));
    Ref<Term> B(new Constant("B"));
    Ref<Term> C(new Constant("C"));
    Ref<Predicate> PA(new Predicate("PA"));
    PA->terms.push_back(A);
    Ref<Predicate> PB(new Predicate("PB"));
    PB->terms.push_back(B);
    Ref<Predicate> PC(new Predicate("PC"));
    PC->terms.push_back(C);
    Ref<Negation> NPC(new Negation());
    NPC->formula.assign<Predicate>(PC);
    Ref<Disjunction> D(new Disjunction());
    D->formulas.push_back(PA.cast<Formula>());
    D->formulas.push_back(PB.cast<Formula>());
    D->formulas.push_back(NPC.cast<Formula>());
    Negater negater;
    Ref<Formula> ND;
    negater.Negate(D.cast<Formula>(),ND);
    std::cout <<"ok" <<  ND->toString() << std::endl;
  } catch(...) {
    std::cout<<"Exception occured"<<std::endl;
  }
}
