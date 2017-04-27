#include <iostream>
#include <gmpxx.h>
#include "include.hpp"

void		getBinoCoef(mpz_t result, unsigned int val1, unsigned int val2)
{
  mpz_t		tmp;
  mpz_t		parent;

  mpz_set_ui(result, 0);
  mpz_init (tmp);
  mpz_init (parent);

  mpz_fac_ui(result, val1);
  mpz_fac_ui(tmp, val2);
  mpz_fac_ui(parent, val1 - val2);
  mpz_mul(tmp, tmp, parent);
  mpz_div(result, result, tmp);
}

void		compute2(unsigned int val1, unsigned int val2)
{
  mpz_t		result;

  mpz_init (result);
  getBinoCoef(result, val1, val2);

  std::cout << val2 << "-combination of a " << val1 << " set:" << std::endl;
  std::cout << result << std::endl;
}
