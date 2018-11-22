#ifndef _REFERENCE_HPP_
#define _REFERENCE_HPP_

#ifndef NULL
#define NULL 0L
#endif

struct Counter {
  int count;
  Counter() { count = 1; }
  void Inc() { ++count; }
  bool Dec() { if (--count == 0) { return true; } return false; }
};

template <typename T>
struct Ref {
  Counter *counter;
  T *pointer;

  void clear() {
    if (counter != NULL && counter->Dec()) { delete counter; delete pointer;}
  }
  template<typename U>
  bool is() const {
    return (dynamic_cast<U*>(pointer) != NULL)?true:false;
  }
  template<typename U>
  void assign(const Ref<U> &cp)  {
    clear();
    pointer  = dynamic_cast<T*>(cp.pointer); counter = cp.counter;
    if (counter != NULL) { counter->Inc();}
  }

  template<typename U>
  Ref<U> cast() const {
    Ref<U> ref;
    ref.template assign<T>(*this);
    return ref;
  }

  Ref() { pointer = NULL; counter = NULL; }
  Ref(T *ptr) {  pointer = NULL; counter = NULL; if (ptr != NULL) { pointer = ptr; counter = new Counter(); } }
  Ref(const Ref<T> &cp) {
    pointer = NULL; counter = NULL;
    assign<T>(cp);
  }

  Ref<T> &operator=(const Ref<T> &cp) {
    assign<T>(cp);
    return *this;
  }

  virtual ~Ref() {
    clear();
  }

  T &operator*() {return *pointer;}
  const T &operator*() const {return *pointer;}

  T *operator->() {return pointer;}
  const T*operator->()const{return pointer;}

  template<typename U>
  U *as() { return dynamic_cast<U*>(pointer); }

  template<typename U>
  const U *as() const { return dynamic_cast<U*>(pointer); }

  bool isNull() const { return pointer == NULL;}
};

template<typename T,typename U>
bool operator==(const Ref<T> & t1, const Ref<U> &t2) {
  return (void*)t1.pointer == (void*)t2.pointer;
}

#include <functional>

namespace std {
  template<typename T>
  struct hash<Ref<T>> {
    std::hash<T*> _hash;
    std::size_t operator()(Ref<T> const&ref) const noexcept { return  _hash(ref.pointer);}
  };
}
#endif
