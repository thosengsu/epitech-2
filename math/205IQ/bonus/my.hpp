//
// my.hpp for 205 in /home/erwan/Tek2/Math/205IQ
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Wed Apr 12 11:31:35 2017 Erwan
// Last update Tue Apr 18 16:35:14 2017 Erwan
//

#ifndef MY_HPP
# define MY_HPP

# include <iostream>
# include <iomanip>
# include <exception>
# include <vector>
# include <math.h>

class IQ
{
public:
  /* CTRO && DTOR */
  IQ(int arg, int mean, int deviation, int max = 200, int min = 0)
    : _mean(mean), _deviation(deviation), _min(min), _max(max), _toDo(arg)
  {
    if (this->_mean < 0 || this->_mean > 200)
      throw (std::invalid_argument(static_cast<std::string>("Mean need to be between 0 and 200.")));
    else if (this->_min > this->_max)
      throw (std::invalid_argument(static_cast<std::string>("Min can't be sup than max.")));
    this->_values.resize(201);
  }

  ~IQ(void) {};

  /* MEMBER FUNCTION */
  void compute(void)
  {
    double	idx = static_cast<double>(this->_min);
    double	nb;
    double	tot = 0;

    while (idx <= static_cast<double>(this->_max))
      {
	nb = this->gauss(idx);
	if (this->_toDo == 3)
	  {
	    std::cout << static_cast<int>(idx) << std::setprecision(2) << std::fixed << " "
		      << (nb * 100) << std::endl;
	    this->_values[static_cast<int>(idx)] = nb * 100;
	    ++idx;
	  }
	else
	  {
	    tot += nb;
	    idx += 0.01;
	  }
      }
    if (this->_toDo == 4)
      std::cout << std::fixed << std::setprecision(1) << tot << "% of people have a IQ inferior to "
		<< this->_max << std::endl;
    else if (this->_toDo == 5)
      std::cout << std::fixed << std::setprecision(1) << tot << "% of people have a IQ between "
		<< this->_min << " and " << this->_max << std::endl;
  }

  /* GETTER SETTER */
  void		setMean(int mean)
  {
    if (mean <= 200 && mean >= 0)
      this->_mean = mean;
  }

  void		setDeviation(int dev)
  {
    if (dev > 0)
      this->_deviation = dev;
  }

  void		setMin(int min)
  {
    if (min >= 0 && min < this->_max)
      this->_min = min;
  }

  void		setMax(int max)
  {
    if (max <= 200 && max > this->_min)
      this->_max = max;
  }

  std::vector<double>	getValues(void) const
  {
    return (this->_values);
  }

  int		getMax(void) const
  {
    return (this->_max);
  }

  int		getMean(void) const
  {
    return (this->_mean);
  }

  int		getDeviation(void) const
  {
    return (this->_deviation);
  }

private:
  double	gauss(double idx)
  {
    double	out;

    out = static_cast<double>((1 / (this->_deviation * sqrt(2 * M_PI))) *
			      (exp(- (pow(idx - this->_mean, 2) / (2 * pow(this->_deviation, 2))))));
    return (out);
  }

  int			_mean;
  int			_deviation;
  int			_min;
  int			_max;
  int			_toDo;
  std::vector<double>	_values;
};

#endif /* !MY_HPP_ */
