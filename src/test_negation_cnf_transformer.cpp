#include "negation_cnf_transformer.hpp"
#include <iostream>

int main() {
    try {
        NegationCNFTransformer transformer;
        if (true) {
            Ref<Predicate> P(new Predicate("P"));
            Ref<Negation> negation(new Negation());
            negation->formula.assign<Predicate>(P);
            Ref<Negation> negation2(new Negation());
            negation2->formula.assign<Negation>(negation);
            Ref<Formula> formula;
            formula.assign<Negation>(negation2);
            std::cout << formula->toString();
            transformer.Transform(formula);
            std::cout << " : " << formula->toString() << std::endl;
        }
        if (true) {
            // ~(A ^ ~(B v C) ^ ~D) 
            // ~A v (B v C) v D
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
            transformer.Transform(formula);
            std::cout <<  " : " << formula->toString() << std::endl;
        }        
        if (true) {
            // Et( Nuit(t) ^ ( Ex Chat(X) ^ ~Color(x,Gris)))
            Ref<Variable> T(new Variable("t"));
            Ref<Variable> X(new Variable("x"));
            Ref<Constant> Gris(new Constant("Gris"));
            Ref<Predicate> Nuit(new Predicate("Nuit"));
            Ref<Predicate> Chat(new Predicate("Chat"));
            Ref<Predicate> Color(new Predicate("Color"));
            Ref<Negation>  N(new Negation());
            Ref<Existantial> ET(new Existantial());
            Ref<Conjunction> C1(new Conjunction());      
            Ref<Existantial> EX(new Existantial());
            Ref<Conjunction> C2(new Conjunction());
            Nuit->terms.push_back(T.cast<Term>());
            Chat->terms.push_back(X.cast<Term>());
            Color->terms.push_back(X.cast<Term>());
            Color->terms.push_back(Gris.cast<Term>());
            N->formula.assign<Predicate>(Color);
            C2->formulas.push_back(Chat.cast<Formula>());
            C2->formulas.push_back(N.cast<Formula>());
            EX->variable = X;
            EX->formula.assign<Conjunction>(C2);
            C1->formulas.push_back(Nuit.cast<Formula>());
            C1->formulas.push_back(EX.cast<Formula>());
            ET->variable = T;
            ET->formula.assign<Conjunction>(C1);
            Ref<Negation> N2(new Negation());
            N2->formula.assign<Existantial>(ET);
            Ref<Formula> formula;
            formula.assign<Negation>(N2);
            std::cout<<formula->toString();
            transformer.Transform(formula);
            std::cout<< " : " << formula->toString() << std::endl;
        }
    } catch(...) {
        std::cout<<"Exception occured"<<std::endl;       
    }
}