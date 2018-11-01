#include <iostream>
#include "quantifier_cnf_transformer.hpp"
#include "logic_node.hpp"
#include "reference.hpp"
#include "exception.hpp"

int main() {
    try {
        QuantifierCNFTransformer transformer;
        if (true) {
            // Et (Nuit(t) => Ax( Chat(x) v ~Gris(t,x)))
            Ref<Term> T(new Variable("t"));
            Ref<Term> X(new Variable("x"));
            Ref<Term> Gris(new Constant("Gris"));
            Ref<Formula> Nuit(new Predicate("Nuit"));
            Ref<Formula> Chat(new Predicate("Chat"));
            Ref<Formula> Color(new Predicate("Color"));
            Ref<Formula>  N(new Negation());
            Ref<Formula> Et(new Existantial());
            Ref<Formula> I(new Implication());      
            Ref<Formula> Ax(new Universal());
            Ref<Formula> D(new Disjunction());
            Nuit.as<Predicate>()->terms.push_back(T);
            Chat.as<Predicate>()->terms.push_back(X);
            Color.as<Predicate>()->terms.push_back(X);
            Color.as<Predicate>()->terms.push_back(Gris);
            N.as<Negation>()->formula = Color;
            D.as<Disjunction>()->formulas.push_back(Chat);
            D.as<Disjunction>()->formulas.push_back(N);
            Ax.as<Universal>()->variables.push_back(X.cast<Variable>());
            Ax.as<Universal>()->formula = D;
            I.as<Implication>()->left = Nuit;
            I.as<Implication>()->right = Ax;
            Et.as<Existantial>()->variables.push_back(T.cast<Variable>());
            Et.as<Existantial>()->formula = I;
            std::cout << Et->toString() << std::endl;
            transformer.Transform(Et);
            std::cout << Et->toString() << std::endl;
        }
    } catch(...) {
        std::cout << "Exception occured" << std::endl;
    }
}