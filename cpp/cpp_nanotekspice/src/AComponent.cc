#include <vector>
#include <string>
#include <exception>
#include <list>
#include <iostream>
#include "AComponent.hh"
#include "enum.hh"
#include "IComponent.hh"

// constructeur /-/ destructeur

nts::AComponent::AComponent(std::vector<nts::InOut> inOut, const std::string& name)
{
  nts::Pin	pin;

  this->_name = name;
  for (auto idx : inOut)
    {
      pin.state = nts::UNDEFINED;
      pin.inOut = idx;
      this->_pins.push_back(pin);
    }
}

nts::AComponent::~AComponent() {
}

// GETTER

nts::Tristate	nts::AComponent::getState(size_t pin) const
{
  return (this->_pins[pin - 1].state);
}

nts::InOut	nts::AComponent::getPinType(size_t pin) const
{
  return (this->_pins[pin - 1].inOut);
}

nts::Tristate	nts::AComponent::getInLinkState(size_t pin)
{
  nts::Tristate	out = nts::UNDEFINED;
  nts::Tristate	tmp;

  for (auto i : this->_inLinks)
    {
      if (i.pinThis == pin)
	{
	  tmp = i.theTarget->Compute(i.pinTarget);
	  if (tmp == nts::TRUE)
	    {
	      out = nts::TRUE;
	      break;
	    }
	  else if (out != nts::TRUE && tmp == nts::FALSE)
	    out = nts::FALSE;
	}
    }
  if (out != nts::UNDEFINED)
    static_cast<AComponent *>(this)->setPin(pin, out);
  return (out);
}

// member functions

void		nts::AComponent::Dump(void) const
{
  std::cout << this->_name << ":" << std::endl;
  for (size_t idx = 0; idx < this->_pins.size(); idx++)
    {
      if (this->_pins[idx].inOut == nts::POWER)
	std::cout << "pin number : " << idx << ", is a power pin, ignored here" << std::endl;
      else
	{
	  std::cout << "pin number : " << idx << ", is an ";
	  if (this->_pins[idx].inOut == nts::INPUT)
	     std::cout << "input pin";
	  else if (this->_pins[idx].inOut == nts::OUTPUT)
	    std::cout << "output pin";

	  std::cout << " with the value : ";
	  if (this->_pins[idx].state == nts::UNDEFINED)
	    std::cout << "undefined." << std::endl;
	  else if (this->_pins[idx].state == nts::TRUE)
	    std::cout << "true." << std::endl;
	  else if (this->_pins[idx].state == nts::FALSE)
	    std::cout << "false." << std::endl;
	}
    }
}

void		nts::AComponent::SetLink(size_t pin_num_this, nts::IComponent &component,
				    size_t pin_num_target)
{
  /*  nts::target	newTarget;

  newTarget.pinThis = pin_num_this;
  newTarget.pinTarget = pin_num_target;
  newTarget.theTarget = &component;

  this->_outLinks.push_back(newTarget);*/

  nts::target	newReceiv;

  newReceiv.pinThis = pin_num_this;
  newReceiv.pinTarget = pin_num_target;
  newReceiv.theTarget = &component;

  this->_inLinks.push_back(newReceiv);
}

const std::string&	nts::AComponent::getName() const
{
  return (this->_name);
}

size_t			nts::AComponent::getMaxPin(void) const
{
  return(this->_pins.size());
}

int			nts::AComponent::isLinked(void) const
{
  if (this->_inLinks.empty())
    return (-1);
  return (0);
}

void		nts::AComponent::setPin(size_t numPin, nts::Tristate state)
{
  this->_pins[numPin - 1].state = state;
}
