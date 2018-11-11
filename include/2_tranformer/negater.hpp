#ifndef _Negater_HPP_
#define _Negater_HPP_

#include <unordered_map>
#include <typeindex>
#include "reference.hpp"
#include "logic_node.hpp"

struct Negater {
  Negater();
  void Negate(Ref<Formula> &);
private:
  void NegateStandard(Ref<Formula> &);
  void NegateNegation(Ref<Formula> &);
  void NegateDisjunction(Ref<Formula> &);
  void NegateConjunction(Ref<Formula> &);
  void NegateExistantial(Ref<Formula> &);
  void NegateUniversal(Ref<Formula> &);
  void NegateImplication(Ref<Formula> &);
  typedef void (Negater::*NegateMethod)(Ref<Formula> &input);
  std::unordered_map<std::type_index, NegateMethod> negater_method_map;
};

#endif
