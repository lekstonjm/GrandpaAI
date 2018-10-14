#include "node.hpp"
#include <sstream>

int NamedNode::_index = 0;

std::string NamedNode::toString() const{
  return name;
}

std::string Function::toString() const {
  std::stringstream ss;
  bool first = true;
  ss << name;
  ss << "(";
  for(auto &term:terms) {
    ss << (first?"":" ^ ") << (term.isNull()?"":term->toString());
    first = false;
  }
  ss << ")";
}

std::string Predicate::toString() const{
  std::stringstream ss;
  bool first = true;
  ss << name;
  ss << "(";
  for(auto &term:terms) {
    ss << (first?"":" ^ ") << (term.isNull()?"":term->toString());
    first = false;
  }
  ss << ")";
  return ss.str();
}

std::string Equality::toString() const {
  std::stringstream ss;
  ss << ( left.isNull()?"":left->toString()) << " = " << (right.isNull()?"":right->toString()) << std::endl;
}

std::string Negation::toString() const {
  std::stringstream ss;
  ss << "~" << "(" << (formula.isNull()?"":formula->toString())<< ")";
  return ss.str();
}

std::string Conjunction::toString() const {
  std::stringstream ss;
  bool first = true;
  ss << "(";
  for(auto &formula:formulas) {
    ss << (first?"":" ^ ") << (formula.isNull()?"":formula->toString());
    first = false;
  }
  ss << ")";
  return ss.str();
}

std::string Disjunction::toString() const {
  std::stringstream ss;
  bool first = true;
  ss << "(" ;
  for(auto &formula:formulas) {
    ss << (first?"":" v ") << (formula.isNull()?"":formula->toString());
    first = false;
  }
  ss << ")";
  return ss.str();
}

std::string Implication::toString()  const {
  std::stringstream ss;
  ss << (head.isNull()?"":head->toString() ) << " => " << (body.isNull()?"":body->toString());
  return ss.str();
}
