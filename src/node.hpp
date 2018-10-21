#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <string>
#include <vector>
#include "exception.hpp"
#include "reference.hpp"
#ifndef NULL
#define NULL 0L
#endif

struct  Node {
  Node() {}
  virtual ~Node() {}
  virtual std::string toString() const = 0;
};

struct NamedNode : virtual Node {
  std::string name;
  NamedNode(const std::string &name_):Node() {
    name = name_;
  }
  virtual std::string toString() const;
private:
  static int _index;
};

struct Term : virtual Node {
  Term():Node(){}
};

struct Constant : Term, NamedNode {
  Constant(const std::string &name):Term(),NamedNode(name){}
};

struct  Variable : Term, NamedNode  {
  Variable(const std::string &name):Term(),NamedNode(name){}
};

struct Function : Term, NamedNode {
  std::vector<Ref<Term>> terms;
  Function(const std::string &name) : Term(),NamedNode(name) {}
  virtual std::string toString() const;
};

struct Formula : virtual Node { };

struct Predicate :  Formula, NamedNode {
    std::vector<Ref<Term>> terms;
    Predicate(const std::string &name):Formula(), NamedNode(name) {}
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
  Ref<Formula> head;
  Ref<Formula> body;
  Implication():Formula(){}
  virtual std::string toString() const;
};

struct ExistantialQuantifier : Formula {
  Ref<Formula> formula;
  Ref<Variable> variable;
  ExistantialQuantifier() {}
  virtual std::string toString() const;
};

struct UniversalQuantifier : Formula {
  Ref<Formula> formula;
  Ref<Variable> variable;
  UniversalQuantifier() {}
  virtual std::string toString() const; 
};
#endif
