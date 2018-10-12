#ifndef _LogicNode_HPP_
#define _LogicNode_HPP_

#include <string>
#include <vector>
#include "exception.hpp"
#include "reference.hpp"
#ifndef NULL
#define NULL 0L
#endif

struct  LogicNode {
  LogicNode() {}
  virtual ~LogicNode() {}
  virtual std::string toString() const = 0;
};

struct NamedNode : virtual LogicNode {
  std::string name;
  NamedNode(const std::string &name_):LogicNode() {
    name = name_;
  }
  virtual std::string toString() const;
private:
  static int _index;
};



struct Term : virtual LogicNode {
  Term():LogicNode(){}
};

struct ArityNode : virtual LogicNode {
  std::vector<Ref<Term>> terms;
  int computeArity() {return terms.size();}
};

struct Constant : Term, NamedNode {
  Constant(const std::string &name):Term(),NamedNode(name){}
};

struct  Variable : Term, NamedNode  {
  Variable(const std::string &name):Term(),NamedNode(name){}
};

struct Function : Term, NamedNode, ArityNode {
  Function(const std::string &name) : Term(),NamedNode(name), ArityNode() {}
  virtual std::string toString() const;
};

struct Formula : virtual LogicNode { };

struct Predicate :  Formula, NamedNode, ArityNode {
    Predicate(const std::string &name):Formula(), NamedNode(name), ArityNode() {}
    virtual std::string toString() const;
};

struct Binary : Formula {
  Ref<Term> right;
  Ref<Term> left;
  Binary():Formula() {}
};

struct Equality : Binary {
  Equality() : Binary() {}
  virtual std::string toString() const;
};

struct Negation : Formula
{
  Negation():Formula() {}
  Ref<Formula> formula;
  virtual std::string toString() const;
};

struct Connective : Formula {
  Connective() : Formula() {}
  std::vector<Ref<Formula> > formulas;
};

struct Conjunction : Connective {
  Conjunction() : Connective() {}
  virtual std::string toString() const;
};

struct Disjunction : Connective {
  Disjunction() : Connective() {}
  virtual std::string toString() const;
};

struct Implication : Binary {
  Implication():Binary(){}
  virtual std::string toString() const;
};

struct Quantifier : Formula {
  Ref<Formula> formula;
  Ref<Variable> variable;
  Quantifier() {}
};

struct Existantial : Quantifier {
  Existantial() {}
  virtual std::string toString() const;
};

struct Universal : Quantifier {
  Universal() {}
  virtual std::string toString() const;
};
#endif
