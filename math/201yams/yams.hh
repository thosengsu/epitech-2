#ifndef YAMS_HH_
# define YAMS_HH_

# include <iostream>
# include <map>
# include <string>

int	checkArg(int ac, char **av);
void	getProba(char **av);
int	getCombinationSize(std::string combination);
int	*getWantedDie(std::string combination, int value1, int value2);

typedef	enum	e_combinationType
  {
    PAIR,
    THREE,
    FOUR,
    FULL,
    STRAIGHT,
    YAMS
  }		CombinationType;

static std::string CombinationName[] =
  {
    "pair",
    "three",
    "four",
    "full",
    "straight",
    "yams"
  };

# define S_PAIR		2
# define S_THREE	3
# define S_FOUR		4
# define S_FULL		5
# define S_STRAIGHT	5
# define S_YAMS		5

#endif /* !YAMS_HH_ */
