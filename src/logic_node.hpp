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

struct Prototype {
  Prototype(const std::string &name_, int arity_) : name(name_), arity(arity_) {}
  std::string name;
  int arity;
};

struct NamedNode : virtual LogicNode {
  std::string name;
  NamedNode(const std::string &name_):LogicNode() {
    name = name_;
  }
  virtual std::string toString() const;
};

struct Term : virtual LogicNode {
  Term():LogicNode(){}
};


struct FunctionalNode : virtual LogicNode {
  FunctionalNode(const std::string &name_, int arity_) {
    prototype = Ref<Prototype>(new Prototype(name_, arity_));
  }
  FunctionalNode(const Ref<Prototype> &prototype_):prototype(prototype_) {    
    InvalidArgumentException::ThrowIf(prototype.isNull());
  }
  std::vector<Ref<Term>> terms;
  Ref<Prototype> prototype;
};

struct Constant : Term, NamedNode {
  Constant(const std::string &name):Term(),NamedNode(name){}
};

struct  Variable : Term, NamedNode  {
  Variable(const std::string &name):Term(),NamedNode(name){}
};


struct Function : Term,  FunctionalNode {
  Function(const Ref<Prototype> &prototype_) : Term(), FunctionalNode(prototype_) {}
  Function(const std::string &name, int arity = 0) : Term(), FunctionalNode(name, arity) {}
  virtual std::string toString() const;
};

struct Formula : virtual LogicNode { };


struct Predicate :  Formula, FunctionalNode {
    Predicate(const Ref<Prototype> &prototype_):Formula(), FunctionalNode(prototype_) {}
    Predicate(const std::string &name, int arity=0):Formula(), FunctionalNode(name, arity) {}
    virtual std::string toString() const;
};

struct Equality : Formula {
  Ref<Term> right;
  Ref<Term> left;
  Equality() : Formula() {}
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

struct Implication : Formula {
  Ref<Formula> right;
  Ref<Formula> left;
  Implication():Formula(){}
  virtual std::string toString() const;
};

struct Quantifier : Formula {
  Ref<Formula> formula;
  std::vector<Ref<Variable>> variables;
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
