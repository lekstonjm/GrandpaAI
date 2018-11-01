#include <iostream>
#include "exception.hpp"
#include "reference.hpp"
#include "logic_node.hpp"
#include "negater.hpp"

int main(int argc, char *argv[])
{
  try {
    Negater negater;
    if (true) {
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
      std::cout << D->toString();
      Ref<Formula> formula;
      formula.assign<Disjunction>(D);
      std::cout << formula->toString();
      negater.Negate(formula);
      std::cout <<  " : " << formula->toString() << std::endl;
    }
    if (true) {
      // ~(A ^ ~(B v C) ^ ~D) 
      // A ^ ~(B v C) ^ ~D
      Ref<Predicate> A(new Predicate("A"));
      Ref<Predicate> B(new Predicate("B"));
      Ref<Predicate> C(new Predicate("C"));
      Ref<Predicate> D(new Predicate("D"));
      Ref<Conjunction> c(new Conjunction());
      Ref<Disjunction> d(new Disjunction());
      Ref<Negation> n(new Negation());
      Ref<Negation> n2(new Negation());
      Ref<Negation> n3(new Negation());
      d->formulas.push_back(B.cast<Formula>());
      d->formulas.push_back(C.cast<Formula>());
      n->formula.assign<Disjunction>(d);
      c->formulas.push_back(A.cast<Formula>());
      c->formulas.push_back(n.cast<Formula>());
      n2->formula.assign<Predicate>(D);
      c->formulas.push_back(n2.cast<Formula>());      
      n3->formula.assign<Conjunction>(c);
      Ref<Formula> formula;
      formula.assign<Negation>(n3);
      std::cout << formula->toString();
      negater.Negate(formula);
      std::cout <<  " : " << formula->toString() << std::endl;
    }
    if (true) {
      // At( Nuit(t) => Ax (Chat(x) => Color(x,Gris) ))
      // Et( Nuit(t) ^ ( Ex Chat(X) ^ ~Color(x,Gris)))
      Ref<Variable> T(new Variable("t"));
      Ref<Variable> X(new Variable("x"));
      Ref<Constant> Gris(new Constant("Gris"));
      Ref<Predicate> Nuit(new Predicate("Nuit"));
      Ref<Predicate> Chat(new Predicate("Chat"));
      Ref<Predicate> Color(new Predicate("Color"));
      Ref<Universal> AllT(new Universal());
      Ref<Implication> IT(new Implication());      
      Ref<Universal> AllX(new Universal());
      Ref<Implication> IX(new Implication());
      Nuit->terms.push_back(T.cast<Term>());
      Chat->terms.push_back(X.cast<Term>());
      Color->terms.push_back(X.cast<Term>());
      Color->terms.push_back(Gris.cast<Term>());
      IX->left = Chat.cast<Formula>();
      IX->right = Color.cast<Formula>();
      AllX->variables.push_back(X);
      AllX->formula = IX.cast<Formula>();
      IT->left = Nuit.cast<Formula>();
      IT->right = AllX.cast<Formula>();
      AllT->variables.push_back(T);
      AllT->formula = IT.cast<Formula>();
      Ref<Formula> formula;
      formula.assign<Universal>(AllT);
      std::cout << formula->toString() ;

      negater.Negate(formula);
      std::cout << " : " << formula->toString() <<  std::endl;
    }
  } catch(...) {
    std::cout<<"Exception occured"<<std::endl;
  }
}
