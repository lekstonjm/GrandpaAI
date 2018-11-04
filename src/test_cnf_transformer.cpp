#include <iostream>
#include "exception.hpp"
#include "reference.hpp"
#include "logic_node.hpp"
#include "cnf_transformer.hpp"

int main() {
    try {
        CNFTransformer transformer;
        if (true) {
            // (At Nuit(t) => (Ax Chat(x) => Couleur(x,t,Gris)))^(Nuit(Maintenant) ^ Chat(Remi))
            Ref<Term> T(new Variable("t"));
            Ref<Term> X(new Variable("x"));
            Ref<Term> Gris(new Constant("Gris"));
            Ref<Term> Remi(new Constant("Remi"));
            Ref<Term> Maintenant(new Constant("Maintenant"));
            Ref<Prototype> NuitPrototype(new Prototype("Nuit",1));
            Ref<Prototype> ChatPrototype(new Prototype("Chat",1));
            Ref<Prototype> CouleurPrototype(new Prototype("Couleur",1));
            Ref<Formula> NuitT(new Predicate(NuitPrototype));
            Ref<Formula> ChatX(new Predicate(ChatPrototype));
            Ref<Formula> CouleurXTGris(new Predicate(CouleurPrototype));
            Ref<Formula> At(new Universal());
            Ref<Formula> It(new Implication());      
            Ref<Formula> Ax(new Universal());
            Ref<Formula> Ix(new Implication());
            NuitT.as<Predicate>()->terms.push_back(T);
            ChatX.as<Predicate>()->terms.push_back(X);
            CouleurXTGris.as<Predicate>()->terms.push_back(X);
            CouleurXTGris.as<Predicate>()->terms.push_back(T);
            CouleurXTGris.as<Predicate>()->terms.push_back(Gris);
            Ix.as<Implication>()->left = ChatX;
            Ix.as<Implication>()->right = CouleurXTGris;
            Ax.as<Universal>()->variables.push_back(X.cast<Variable>());
            Ax.as<Universal>()->formula = Ix;
            It.as<Implication>()->left = NuitT;
            It.as<Implication>()->right = Ax;
            At.as<Universal>()->variables.push_back(T.cast<Variable>());
            At.as<Universal>()->formula = It;
            Ref<Formula> NuitMaintenant(new Predicate(NuitPrototype));
            NuitMaintenant.as<Predicate>()->terms.push_back(Maintenant);
            Ref<Formula> ChatRemi(new Predicate(ChatPrototype));
            ChatRemi.as<Predicate>()->terms.push_back(Remi); 
            Ref<Formula> input(new Conjunction());
            input.as<Conjunction>()->formulas.push_back(At);
            input.as<Conjunction>()->formulas.push_back(NuitMaintenant);
            input.as<Conjunction>()->formulas.push_back(ChatRemi);
            std::cout << input->toString() ;
            transformer.Transform(input);
            // A(t,x) ( ~Nuit(t) V ~Chat(x) V Couleur(x,t,Gris) )            
            std::cout << " : " << input->toString() <<  std::endl;            
           
        }
    } catch(...) {
        std::cout<< "Exception occured" << std::endl;
    }
}