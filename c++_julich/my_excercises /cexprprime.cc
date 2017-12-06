#include <cstddef>

constexpr bool is_prime_rec(size_t number, size_t c)
{
  return (c*c>number)?true:(number % c == 0)?false:is_prime_rec(number, c+1);
}
constexpr bool is_prime(size_t number)
{
  return (number<=1)?false:is_prime_rec(number,2);
}
int main()
{
  //  constexpr unsigned N=1000003;
  constexpr unsigned N=4;
  static_assert(is_prime(N),"Not a prime");
}

