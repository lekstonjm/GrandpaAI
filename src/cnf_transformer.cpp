#include "cnf_transformer.hpp"

void CNFTransformer::Transform(Ref<Formula> &input) {
  implication_transformer.Transform(input);
  negation_transformer.Transform(input);
  quantifier_transformer.Transform(input);
  connective_transformer.Transform(input);
}
