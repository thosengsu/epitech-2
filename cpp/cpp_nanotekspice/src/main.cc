#include <iostream>
#include <stdexcept>
#include <regex>
#include "my.hh"
#include "Parser.hh"
#include "Error.hh"
#include "graph.hh"
#include "shell.hh"

void			exec(nts::graph *graph)
{
  nts::sh::shell	shell(graph->components, graph->inputs, graph->outputs);

  shell.sh();

  for (auto i : graph->components)
    delete i;
}

void			applyArg(char **av, nts::graph *graph)
{
  size_t		idx = 2;
  std::regex		reg = static_cast<std::regex>("^[a-zA-Z0-9]+=[0-1]{1}$");
  std::string		buff;
  std::string		name;
  int			value;
  nts::AComponent	*ptr;

  while (av[idx] != NULL)
    {
      buff = av[idx];
      if (std::regex_match(buff, reg) != 1)
	throw(std::invalid_argument(buff + static_cast<std::string>(" : Invalid argument.")));

      name = buff.substr(0, buff.find_first_of('='));
      value = std::stoi(buff.substr(buff.find_first_of('=') + 1));

      ptr = static_cast<nts::AComponent *>(graph->getInput(name));
      if (ptr == NULL)
	throw(std::invalid_argument(buff + static_cast<std::string>(" : Input not defined.")));
      ptr->setPin(1, (value == 1) ? nts::TRUE : nts::FALSE);
      ++idx;
    }
  for (auto i : graph->inputs)
    {
      if (static_cast<nts::AComponent *>(i)->getState(1) == nts::UNDEFINED)
	throw(std::invalid_argument(static_cast<nts::AComponent *>(i)->getName() +
				    static_cast<std::string>(" : Input state must be define.")));
    }
}

int			main(int ac, char **av)
{
  nts::Parser		*parser;

  try
    {
      checkArg(ac, av);
      parser = readFile(av[1]);
      applyArg(av, parser->getGraph());
      exec(parser->getGraph());
    }
  catch (const std::invalid_argument &error)
    {
      std::cerr << av[0] << ": " << error.what() << std::endl;
      std::cerr << av[0] << " <config file> inputName=inputState(0,1)"<< std::endl;
    }
  catch (const nts::error::file_error &error)
    {
      std::cerr << av[0] << " : Error while reading " << av[1] << ":" << std::endl;
      std::cerr << error.what() << std::endl;
    }
  catch (const std::exception &error)
    {
      std::cerr << av[0] << ": " << error.what() << std::endl;
    }
  return (0);
}
