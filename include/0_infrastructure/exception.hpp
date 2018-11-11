#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

struct InvalidArgumentException {
  InvalidArgumentException() {}
  static void ThrowNull(void *var);
  static void ThrowIf(bool);
};

struct NotImplementedException {
  NotImplementedException() {}
  static void Throw();
};
#endif
