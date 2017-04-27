#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <fstream>
#include <regex>

void		checkFile(const std::string &fileName)
{
  struct stat	buff;
  std::string	errorMsg = fileName + ": ";
  std::ifstream	file;

  if (stat(fileName.c_str(), &buff) == -1)
    {
      errorMsg += "No such file.";
      throw(std::invalid_argument(errorMsg.c_str()));
    }
  else if (S_ISREG(buff.st_mode) != 1)
    {
      errorMsg += "Is not a regular file.";
      throw(std::invalid_argument(errorMsg.c_str()));
    }
  file.open(fileName);
  if (!file.good())
    {
      errorMsg += "Can't read the file, check the rights.";
      throw(std::invalid_argument(errorMsg.c_str()));
    }
  file.close();
}

void		checkInputs(int ac, char * const *av)
{
  std::regex	reg = static_cast<std::regex>("^[a-zA-Z0-9]+=[0-1]{1}$");
  int		n = 2;

  while (n < ac)
    {
      if (std::regex_match(av[n], reg) != 1)
	throw(std::invalid_argument(static_cast<std::string>("Bad format for argument ") +
				    std::to_string(n + 1) + static_cast<std::string>(".")));
      ++n;
    }
}

void		checkArg(int ac, char * const *av)
{
  std::string	fileName;

  if (ac < 2)
    throw(std::invalid_argument("Need at least config file's name at argument."));
  fileName = av[1];
  checkFile(fileName);
  checkInputs(ac, av);
}
