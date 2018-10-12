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

struct Term;
struct ArityNode : virtual  Node {
  ArityNode(int arity) : Node() {
    InvalidArgumentException::ThrowIf(arity < 0);
    _arity = arity;
  }
  void setTerms(const std::vector<Term*>& terms);
  std::vector<Term*>& getTerms();
protected:
  int _arity;
  std::vector<Term*> _terms;
};

inline void ArityNode::setTerms(const std::vector<Term*>& terms) {
  InvalidArgumentException::ThrowIf(terms.size() != _arity);
  _terms = terms;
}
inline std::vector<Term*> &ArityNode::getTerms() {
  return _terms;
}

struct Term : NamedNode {
  Term(const std::string &name) : NamedNode(name) {}
};

struct Constant : Term {
  Constant(const std::string &name):Term(name){}
};

struct  Variable : Term  {
  Variable(const std::string &name):Term(name){}
};

struct Function : Term, ArityNode {
  Function(const std::string &name, int arity) : Term(name), ArityNode(arity) {}
  virtual std::string toString() const;
};

struct Formula : virtual Node {
};

struct Predicate :  Formula, NamedNode, ArityNode {
    Predicate(const std::string &name, int arity):Formula(), NamedNode(name), ArityNode(arity) {}
    virtual std::string toString() const;
};

struct Negation : Formula
{
  Negation():Formula() { node = NULL; }
  Ref<Node> node;
  virtual std::string toString() const;
};

struct Connective : Formula {
  Connective() : Formula() {}
  std::vector<Ref<Node> > nodes;
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
  Implication():Formula() { premice = NULL; body = NULL; }
  Node *premice;
  Node *body;
  virtual std::string toString() const;
};

#endif
