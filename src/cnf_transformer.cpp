#include "cnf_transformer.hpp"
void CNFTransformer::Transform(const Ref<Formula> &input, Ref<Formula> &output) {
  TransformImplication(input, output);
}
void CNFTransformer::TransformImplication(const Ref<Formula> &, Ref<Formula> &) {
  
}
