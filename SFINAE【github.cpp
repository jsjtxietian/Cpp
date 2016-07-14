#include <type_traits>
#include <utility>
#include <cstdint>

struct ICounter {};
struct Counter: public ICounter 
{
  void increase() 
  {
    // impl
  }
};

template <typename T> 
void inc_counter(
  T& counterObj, 
  typename std::enable_if<
    std::is_base_of<ICounter, T>::value
  >::type* = nullptr )
{
  counterObj.increase();  
}

template <typename T> 
void inc_counter(
  T& counterInt,
  typename std::enable_if<
    std::is_integral<T>::value
  >::type* = nullptr )
{
  ++counterInt;
}

int main() 
{
  Counter cntObj;
  uint32_t cntUI32;

  // blah blah blah
  inc_counter(cntObj); // OK!
  inc_counter(cntUI32); // OK!
}
