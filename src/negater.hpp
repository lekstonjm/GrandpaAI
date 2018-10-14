 #ifndef _Negater_HPP_
 #define _Negater_HPP_

 #include <unordered_map>
 #include <typeindex>
#include "reference.hpp"
#include "node.hpp"

struct Negater {
  typedef void (Negater::*NegateMethod)(const Ref<Formula> &input, Ref<Formula> &output);
  std::unordered_map<std::type_index, NegateMethod> negater_method_map;
  Negater();
  void Negate(const Ref<Formula> &, Ref<Formula> &);
  void NegatePredicate(const Ref<Formula> &, Ref<Formula> &);
  void NegateNegation(const Ref<Formula> &, Ref<Formula> &);
  void NegateDisjunction(const Ref<Formula> &, Ref<Formula> &);
  void NegateConjunction(const Ref<Formula> &, Ref<Formula> &);
};

#endif
