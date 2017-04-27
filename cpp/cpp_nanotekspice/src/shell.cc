#include <string>
#include <regex>
#include <iostream>
#include <csignal>
#include "shell.hh"
#include "AComponent.hh"
#include "IComponent.hh"
#include "In.hh"
#include "Out.hh"

static bool	g_loop = true;

nts::sh::shell::shell(std::vector<nts::IComponent *> components,
		      std::vector<nts::IComponent *> in,
		      std::vector<nts::IComponent *> out)
{
  this->_running = true;
  this->_cmd = "";
  this->_components = components;
  this->_in = in;
  this->_out = out;
}

nts::sh::shell::~shell()
{
}

void			nts::sh::shell::Compare()
{
  this->_cmd = this->epurString(this->_cmd);

  if (this->_cmd == "exit")
    this->_running = false;
  else if (this->_cmd == "help")
    this->affHelp();
  else if (this->_cmd == "dump")
    this->Dump();
  else if (this->_cmd == "simulate")
    this->Simulate();
  else if (this->_cmd == "display")
    this->Display();
  else if (this->_cmd == "loop")
    this->loop();
  else if (std::regex_match(this->_cmd, static_cast<std::regex>("^[a-zA-Z0-9]+=[0-1]{1}$")) == 1)
    {
      for (size_t idx = 0; idx < this->_cmd.size(); idx++)
	{
	  if (this->_cmd[idx] == '=')
	    this->changeInput();
	}
    }
  else if (this->_cmd != "")
    std::cerr << this->_cmd << " : Unknow command. Use help to see all possible commands." << std::endl;
}

void			nts::sh::shell::affHelp() const
{
  std::cout << "\t-----USAGE-----" << std::endl;
  std::cout << std::endl;
  std::cout << "Possible commands:"<< std::endl;
  std::cout << "inputName=Value[0,1]" << std::endl;
  std::cout << "simulate -- launch a simulation" << std::endl;
  std::cout << "loop -- launch simulations until user stop it" << std::endl;
  std::cout << "display -- print all output values" << std::endl;
  std::cout << "dump -- diplay informations about all component" << std::endl;
  std::cout << "exit -- exit the program." << std::endl;
}

void			nts::sh::shell::sh()
{
  this->Simulate();
  this->Display();
  std::cout << "> ";
  while (this->_running == true&& std::getline(std::cin, this->_cmd))
    {
      this->Compare();
      if (this->_running == true)
	std::cout << "> ";
    }
}

void			nts::sh::shell::Dump() const
{
  for (auto i : this->_components)
    i->Dump();
}

void			nts::sh::shell::changeInput()
{
  std::string		input;
  std::string		value;
  size_t		idx = 0;

  idx = this->_cmd.find_first_of('=');
  input = this->_cmd.substr(0, idx);
  value = this->_cmd.substr(idx + 1, this->_cmd.size());
  for (auto i : this->_in)
    {
      if (static_cast<nts::AComponent *>(i)->getName() == input)
	{
	  if (value == "1")
	    static_cast<nts::AComponent *>(i)->setPin(1, nts::TRUE);
	  else if (value == "0")
	    static_cast<nts::AComponent *>(i)->setPin(1, nts::FALSE);
	  return ;
	}
    }
  std::cerr << input << " : is not defined, can't change the value" << std::endl;
}

void			nts::sh::shell::Simulate()
{
  for (auto i : this->_out)
    i->Compute(1);

  for (auto j : this->_in)
    {
      if (static_cast<nts::In *>(j)->getInType() == nts::InputType::CLOCK)
	{
	  if (static_cast<nts::In *>(j)->getState(1) == nts::TRUE)
	    static_cast<nts::In *>(j)->setPin(1, nts::FALSE);
	  else if (static_cast<nts::In *>(j)->getState(1) == nts::FALSE)
	    static_cast<nts::In *>(j)->setPin(1, nts::TRUE);
	}
    }
}

void			nts::sh::shell::Display()
{
  for (auto i : this->_out)
    std::cout << static_cast<AComponent *>(i)->getName() << "=" << static_cast<AComponent *>(i)->getState(1) << std::endl;
}

static void		signal_fct(__attribute__((unused))int signal)
{
  g_loop = false;
}

void			nts::sh::shell::loop()
{
  signal(SIGINT, signal_fct);
  g_loop = true;
  while (g_loop)
    this->Simulate();
  signal(SIGINT, NULL);
}

std::string	nts::sh::shell::epurString(std::string const& str) const
{
  std::string	out;

  for (size_t n = 0 ; n < str.size() ; n++)
    {
      if (str[n] != ' ' && str[n] != '\t')
	out += str[n];
    }
  return (out);
}
