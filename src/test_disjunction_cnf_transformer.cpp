#include "disjunction_cnf_transformer.hpp"
#include "logic_node.hpp"
#include "reference.hpp"
#include "exception.hpp"
#include <iostream>

int main() {
    Ref<Formula> c1(new Conjunction());
    Ref<Formula> c2(new Conjunction());
    Ref<Formula> d1(new Disjunction());
    Ref<Formula> p1(new Predicate("P1"));
    Ref<Formula> p2(new Predicate("P2"));
    Ref<Formula> p3(new Predicate("P3"));
    Ref<Formula> p4(new Predicate("P4"));
    Ref<Formula> p5(new Predicate("P5"));
    Ref<Formula> p6(new Predicate("P6"));
    Ref<Formula> p7(new Predicate("P7"));
    c1.as<Conjunction>()->formulas.push_back(p1);
    c1.as<Conjunction>()->formulas.push_back(p2);
    c1.as<Conjunction>()->formulas.push_back(p3);
    c2.as<Conjunction>()->formulas.push_back(p4);
    c2.as<Conjunction>()->formulas.push_back(p5);
    c2.as<Conjunction>()->formulas.push_back(p6);
    d1.as<Disjunction>()->formulas.push_back(p7);
    d1.as<Disjunction>()->formulas.push_back(c1);
    d1.as<Disjunction>()->formulas.push_back(c2);
    // ( P7 v (P1 ^ P2 ^ P3) v (P4 ^ P5 ^ P6) )
    std::cout << d1->toString() << std::endl;
    DisjunctionCNFTransformer transformer;
    transformer.Transform(d1);
    // ( P7 v P1 v P4) ^ (P7 v P1 v P5) ^ (P7 v P1 v P6 ) ^ (P7 v P2 v P4) ^ (P7 v P2 v P5)...
    std::cout << d1->toString() << std::endl;
}
