#ifndef INCLUDE_HPP_
# define INCLUDE_HPP_

# include <gmpxx.h>

int	checksArgs(int ac, char **av);
int	getArgs(char *str);
void	getBinoCoef(mpz_t result, unsigned int val1, unsigned int val2);
void	compute1(unsigned int val);
void	compute2(unsigned int val, unsigned int val2);

#endif // !INCLUDE_HPP_
