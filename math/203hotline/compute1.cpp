#include <iostream>
#include <iomanip>
#include <gmpxx.h>
#include <math.h>
#include <ctime>
#include "include.hpp"

void		binomialLaw(unsigned int val)
{
  mpf_t		proba;
  mpz_t		coef;
  mpf_t		coeff;
  mpf_t		tmp;
  mpf_t		tmp2;
  mpf_t		total;
  double	P = val / (3600.0 * 8.0);
  clock_t	time = clock();

  mpf_init(proba);
  mpz_init(coef);
  mpf_init(coeff);
  mpf_init(tmp);
  mpf_init(tmp2);
  mpf_init_set_d(total, 0.0);

  std::cout << "Binomial distribution:" << std::endl;

  for (unsigned int i = 0; i <= 3500 ; i++)
    {
      getBinoCoef(coef, 3500, i);
      mpf_set_z(coeff, coef);

      mpf_set_d(tmp, P);
      mpf_pow_ui(tmp, tmp, i);

      mpf_set_d(tmp2, static_cast<double>(1.0 - P));
      mpf_pow_ui(tmp2, tmp2, 3500 - i);

      mpf_mul(proba, tmp2, tmp);
      mpf_mul(proba, proba, coeff);

      if (i > 25)
	mpf_add(total, total, proba);

      if (i <= 50)
	std::cout << i << " -> " << std::fixed << std::setprecision(3) << proba;
      else if (mpf_cmp_ui(total, 100) <= 0)
	break;


      if (i == 5 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35 || i == 41 || i == 47)
	std:: cout << std::endl;
      else if (i != 50)
	std::cout << "\t";
    }
  std::cout << std::endl;

  mpf_set_d(tmp, 100.0);
  mpf_mul(total, total, tmp);
  std::cout << "overload: " << std::fixed << std::setprecision(1) << total << "%" << std::endl;
  double	computTime = (double)(((double)(clock() - time)) / CLOCKS_PER_SEC);
  computTime *= 1000;
  std::cout << "computation time: " << computTime << "ms" << std::endl;
  std::cout << std::endl;
}

void		poissonLaw(unsigned int val)
{
  mpf_t		lowAff;
  mpf_t		proba;
  mpf_t		tmp;
  mpz_t		tmp2;
  double	P = 3500.0 / ((3600.0 * 8.0) / (double)(val));
  double	ex = exp(-P);
  mpf_t		total;
  clock_t	time = clock();

  mpf_init_set_d(lowAff, 0.001);
  mpf_init(proba);
  mpf_init(tmp);
  mpz_init(tmp2);
  mpf_init_set_d(total, 0.0);

  std::cout << "Poisson distribution:" << std::endl;
  for (unsigned int i = 0; i <= 10000; i++)
    {
      mpf_set_d(tmp, P);
      mpf_pow_ui(tmp, tmp, static_cast<double>(i));

      mpz_fac_ui(tmp2, i);

      mpf_set_d(proba, ex);
      mpf_mul(proba, proba, tmp);

      mpf_set_z(tmp, tmp2);
      mpf_div(proba, proba, tmp);

      if (i > 25)
	mpf_add(total, total, proba);

      if (i <= 50)
	std::cout << i << " -> " << std::fixed << std::setprecision(3) << proba;
      else if (mpf_cmp_ui(total, 100) <= 0)
	break;

      if (i == 5 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35 || i == 41 || i == 47)
	std:: cout << std::endl;
      else if (i != 50)
	std::cout << "\t";
    }
  mpf_set_d(tmp, 100.0);
  mpf_mul(total, total, tmp);
  std::cout << std::endl;
  std::cout << "overload: " << std::fixed << std::setprecision(1) << total << "%" << std::endl;
  double	computTime = (double)(((double)(clock() - time)) / CLOCKS_PER_SEC);
  computTime *= 1000;
  std::cout << "computation time: " << computTime << "ms" << std::endl;
}

void		compute1(unsigned int arg)
{
  binomialLaw(arg);
  poissonLaw(arg);
}


/*
**  n(n - 1) ... (n - k + 1)
**---------------------------
**     k(k-1)..... 2.1
*/

/*
**
*/

//utiliser bibliotheque des grands nombres.
//a vérifier
//p < 0.1;
//n > 50;
//np< 10;
