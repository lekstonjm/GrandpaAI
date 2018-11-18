#include <iostream>
#include "skolemization.hpp"
#include "logic_node.hpp"
#include "reference.hpp"
#include "exception.hpp"

int main() {
    try {
        Skolemization transformer;
        if (true) {
            // At (Nuit(t) => Ex( Chat(x) v ~Gris(t,x)))
            Ref<Term> T(new Variable("t"));
            Ref<Term> X(new Variable("x"));
            Ref<Term> Gris(new Constant("Gris"));
            Ref<Formula> Nuit(new Predicate("Nuit"));
            Nuit.as<Predicate>()->prototype->arity = 1;
            Ref<Formula> Chat(new Predicate("Chat"));
            Chat.as<Predicate>()->prototype->arity = 1;
            Ref<Formula> Color(new Predicate("Color"));
            Color.as<Predicate>()->prototype->arity = 2;            
            Ref<Formula>  N(new Negation());
            Ref<Formula> At(new Universal());
            Ref<Formula> I(new Implication());      
            Ref<Formula> Ex(new Existantial());
            Ref<Formula> D(new Disjunction());
            Nuit.as<Predicate>()->terms.push_back(T);
            Chat.as<Predicate>()->terms.push_back(X);
            Color.as<Predicate>()->terms.push_back(X);
            Color.as<Predicate>()->terms.push_back(Gris);
            N.as<Negation>()->formula = Color;
            D.as<Disjunction>()->formulas.push_back(Chat);
            D.as<Disjunction>()->formulas.push_back(N);
            Ex.as<Existantial>()->variables.push_back(X.cast<Variable>());
            Ex.as<Existantial>()->formula = D;
            I.as<Implication>()->left = Nuit;
            I.as<Implication>()->right = Ex;
            At.as<Universal>()->variables.push_back(T.cast<Variable>());
            At.as<Universal>()->formula = I;
            std::cout << At->toString() << std::endl;
            transformer.Transform(At);
            std::cout << At->toString() << std::endl;
        }
    } catch(...) {
        std::cout << "Exception occured" << std::endl;
    }
}