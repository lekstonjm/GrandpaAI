#include "node.hpp"
#include <sstream>

int NamedNode::_index = 0;

std::string NamedNode::toString() const{
  return name;
}


std::string Function::toString() const {
  std::stringstream ss;
  ss << name << " \\" << _arity;
  return ss.str();
}

std::string Predicate::toString() const{
  std::stringstream ss;
  ss << name << "\\" << _arity;
  return ss.str();
}

std::string Negation::toString() const {
  std::stringstream ss;
  ss << "~" << "(" << ((node.isNull())?"":node->toString())<< ")";
  return ss.str();
}

std::string Conjunction::toString() const {
  std::stringstream ss;
  bool first = true;
  ss << "(";
  for(auto &node:nodes) {
    ss << ((first)?"":" ^ ") << ((node.isNull())?"":node->toString());
    first = false;
  }
  ss << ")";
  return ss.str();
}

std::string Disjunction::toString() const {
  std::stringstream ss;
  bool first = true;
  ss << "(" ;
  for(auto &node:nodes) {
    ss << ((first)?"":" v ") << ((node.isNull())?"":node->toString());
    first = false;
  }
  ss << ")";
  return ss.str();
}

std::string Implication::toString()  const {
  std::stringstream ss;
  ss << ( (premice!= NULL)?premice->toString():"") << " => " << ((body != NULL)?body->toString():"");
  return ss.str();
}
