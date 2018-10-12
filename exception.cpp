#include "exception.hpp"
#ifndef NULL
#define NULL 0L
#endif

void InvalidArgumentException::ThrowNull(void *var) {
  if (var == NULL) {
    throw InvalidArgumentException();
  }
}

void InvalidArgumentException::ThrowIf(bool condition) {
  if (condition) {
    throw InvalidArgumentException();
  }
}
