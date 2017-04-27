#include <map>
#include <vector>
#include <string>
#include "comp4071.hh"
#include "orGate.hh"
#include "IComponent.hh"
#include "AComponent.hh"

static std::vector<nts::InOut>		getTypeTab(void)
{
  std::vector<nts::InOut>		out;

  out.push_back(nts::INPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::POWER);
  out.push_back(nts::INPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::INPUT);
  return (out);
}

nts::comp4071::comp4071(const std::string& name)
  : AComponent(getTypeTab(), name)
{
  this->_gates[3] = new nts::orGate;
  this->_gates[4] = new nts::orGate;
  this->_gates[10] = new nts::orGate;
  this->_gates[11] = new nts::orGate;
}

nts::comp4071::~comp4071() {
}

void					nts::comp4071::linkGates()
{
  bool					state = false;

  for (size_t idx = 0; idx < this->_pins.size(); idx++)
    {
      if (this->_pins[idx].inOut == nts::OUTPUT && state == false)
	{
	  this->_gates[idx + 1]->editEntrie(0, this->_pins[idx - 1].state);
	  this->_gates[idx + 1]->editEntrie(1, this->_pins[idx - 2].state);
	  state = true;
	}
      else if (this->_pins[idx].inOut == nts::OUTPUT && state == true)
	{
	  this->_gates[idx + 1]->editEntrie(0, this->_pins[idx + 1].state);
	  this->_gates[idx + 1]->editEntrie(1, this->_pins[idx + 2].state);
	  state = false;
	}
    }
}

nts::Tristate				nts::comp4071::Compute(size_t pin_num_this)
{
  if (pin_num_this == 3)
    {
      getInLinkState(pin_num_this - 1);
      getInLinkState(pin_num_this - 2);
    }
  else if (pin_num_this == 4)
    {
      getInLinkState(pin_num_this + 1);
      getInLinkState(pin_num_this + 2);
    }
  else if (pin_num_this == 10)
    {
      getInLinkState(pin_num_this - 1);
      getInLinkState(pin_num_this - 2);
    }
  else if (pin_num_this == 11)
    {
      getInLinkState(pin_num_this + 1);
      getInLinkState(pin_num_this + 2);
    }
  this->linkGates();
  return (this->_gates[pin_num_this]->compute());
}
