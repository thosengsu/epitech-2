#include <string>
#include <vector>
#include "tekSpice.hh"
#include "IComponent.hh"
#include "comp4001.hh"
#include "comp4011.hh"
#include "comp4030.hh"
#include "comp4069.hh"
#include "comp4071.hh"
#include "comp4081.hh"
#include "In.hh"
#include "Out.hh"

nts::tekSpice::tekSpice()
{
  this->_names.push_back("4001");
  this->_names.push_back("4011");
  this->_names.push_back("4030");
  this->_names.push_back("4069");
  this->_names.push_back("4071");
  this->_names.push_back("4081");
  this->_names.push_back("input");
  this->_names.push_back("output");
  this->_names.push_back("clock");
  this->_names.push_back("true");
  this->_names.push_back("false");
  this->_fct.push_back(std::bind(&tekSpice::create4001, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::create4011, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::create4030, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::create4069, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::create4071, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::create4081, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::createIn, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::createOut, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::createClock, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::createTrue, this, std::placeholders::_1));
  this->_fct.push_back(std::bind(&tekSpice::createFalse, this, std::placeholders::_1));
}

nts::tekSpice::~tekSpice() {
}

nts::IComponent			*nts::tekSpice::createComponent(const std::string& type,
							   const std::string& value)
{
  for (size_t idx = 0; idx < this->_names.size(); idx++)
    {
      if (this->_names[idx] == type)
	return (this->_fct[idx](value));
    }
  return (NULL);
}

nts::IComponent			*nts::tekSpice::createIn(const std::string& value)
{
  return (new nts::In(value, nts::InputType::NORMAL));
}

nts::IComponent			*nts::tekSpice::createOut(const std::string& value)
{
  return (new nts::Out(value));
}

nts::IComponent			*nts::tekSpice::createClock(const std::string& value)
{
  return (new nts::In(value, nts::InputType::CLOCK));
}

nts::IComponent			*nts::tekSpice::createTrue(const std::string& value)
{
  return (new nts::In(value, nts::InputType::TRUE));
}

nts::IComponent			*nts::tekSpice::createFalse(const std::string& value)
{
  return (new nts::In(value, nts::InputType::FALSE));
}

nts::IComponent			*nts::tekSpice::create4001(const std::string& value)
{
  return (new nts::comp4001(value));
}

nts::IComponent			*nts::tekSpice::create4011(const std::string& value)
{
  return (new nts::comp4011(value));
}

nts::IComponent			*nts::tekSpice::create4030(const std::string& value)
{
  return (new nts::comp4030(value));
}

nts::IComponent			*nts::tekSpice::create4069(const std::string& value)
{
  return (new nts::comp4069(value));
}

nts::IComponent			*nts::tekSpice::create4071(const std::string& value)
{
  return (new nts::comp4071(value));
}

nts::IComponent			*nts::tekSpice::create4081(const std::string& value)
{
  return (new nts::comp4081(value));
}
