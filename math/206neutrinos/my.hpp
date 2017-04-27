#ifndef MY_HPP_
# define MY_HPP_

# include <cstdlib>
# include <cmath>
# include <cstdio>
# include <iostream>
# include <iomanip>

class My
{
public :
  My(char *n, char *arith, char *harmo, char *standart)
  {
    this->_n = std::atoi(n);
    this->_arith = std::atof(arith);
    this->_harmo = std::atof(harmo);
    this->_standart = std::atof(standart);
    this->_resN = this->_n + 1;
    this->_resArith = 0;
    this->_resHarmo = 0;
    this->_resEct = 0;
    this->_resQuadra = 0;
  }

  ~My() {}

  void		reset()
  {
    this->_n = this->_resN;
    this->_arith = this->_resArith;
    this->_harmo = this->_resHarmo;
    this->_standart = this->_resEct;
    this->_resN = this->_n + 1;
    this->_resArith = 0;
    this->_resHarmo = 0;
    this->_resEct = 0;
    this->_resQuadra = 0;
  }

  int		run()
  {
     bool		finito = false;
     std::string	str = "";
     double		n;

     while (finito == false)
       {
	 std::cout << "indtast din vaerdi : ";
	 std::cin >> str;
	 if (str != "")
	   {
	     if (str.compare("ENDE") == 0)
	       finito = true;
	     else if (My::checkPrompt(str) != 84)
	       {
		 n = std::atof(str.c_str());
		 My::moyArith(n);
		 My::moyQuadra(n);
		 My::moyHarmo(n);
		 My::EcartType(n);
		 My::aff();
	       }
	     else
	       return (84);
	   }
	 My::reset();
	 str = "";
       }
  }

  int		checkPrompt(const std::string& str)
  {
    for (int idx = 0; str[idx] != '\0'; idx++)
      {
	if (str[idx] < '0' || str[idx] > '9')
	  return (84);
      }
    return (0);
  }

  void		aff() const
  {
    std::cout << this->_resEct << " " << this->_resArith << " " << _resQuadra << " " << _resHarmo << std::endl;
    std::cout << "\tantal mãlinder :\t" << this->_resN << std::endl;
    std::cout << "\tstandardafvilgelse :\t" << std::setprecision(2) << std::fixed << this->_resEct << std::endl;
    std::cout << "\taritmetisk gennemsnit :\t" << std::setprecision(2) << std::fixed << this->_resArith << std::endl;
    std::cout << "\tkvadratisk gennemsnit :\t" << std::setprecision(2) << std::fixed << this->_resQuadra << std::endl;
    std::cout << "\tharmonisk  gennemsnit :\t" << std::setprecision(2) << std::fixed << this->_resHarmo << std::endl;
  }

  void		moyArith(double n)
  {
    this->_resArith = ((this->_arith * this->_n) + n) / (this->_resN);
  }

  void		moyQuadra(double n)
  {
    double	tmp = (((std::pow(this->_standart, 2) + std::pow(this->_arith, 2)) * this->_n) + std::pow(n, 2));
    double	tmp2 = (tmp / this->_resN);
    this->_resQuadra = std::sqrt(tmp2);
  }

  void		moyHarmo(double n)
  {
    this->_resHarmo = (this->_resN / ((1 / n) + (this->_n / this->_harmo)));
  }

  void		EcartType(double n)
  {
    double	tmp;

    tmp = (((std::pow(this->_standart, 2) + std::pow(this->_arith, 2)) * this->_n) + std::pow(n, 2)) / this->_resN;
    tmp -= std::pow(this->_resArith, 2);
    this->_resEct = std::sqrt(tmp);
  }

private :
  int		_n;
  int		_resN;
  double	_arith;
  double	_harmo;
  double	_standart;
  double	_resArith;
  double	_resHarmo;
  double	_resEct;
  double	_resQuadra;
};

#endif // MY_HPP_
