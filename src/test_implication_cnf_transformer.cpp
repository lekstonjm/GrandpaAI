#include "implication_cnf_transformer.hpp"
#include <iostream>

int main() {
    try {
        ImplicationCNFTransformer transformer;
        if (true) {
            Ref<Implication> I(new Implication());
            Ref<Predicate> A(new Predicate("A"));
            Ref<Predicate> B(new Predicate("B"));
            I->left.assign<Predicate>(A);
            I->right.assign<Predicate>(B);

            Ref<Formula> input;
            input.assign<Implication>(I);
            std::cout << input->toString();
            transformer.Transform(input);
            std::cout << " : " << input->toString() <<  std::endl;
        }
        if (true) {
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
            AllX->variable = X;
            AllX->formula = IX.cast<Formula>();
            IT->left = Nuit.cast<Formula>();
            IT->right = AllX.cast<Formula>();
            AllT->variable = T;
            AllT->formula = IT.cast<Formula>();
            Ref<Formula> input;
            input.assign<Universal>(AllT);
            std::cout << input->toString() ;
            transformer.Transform(input);
            std::cout << " : " << input->toString() <<  std::endl;            
        }
    } catch (...) {
        std::cout<<"Exception occured"<<std::endl;
    }
}