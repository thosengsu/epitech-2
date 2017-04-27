#include <map>
#include <vector>
#include <string>
#include "comp4069.hh"
#include "invertGate.hh"
#include "IComponent.hh"
#include "AComponent.hh"

static std::vector<nts::InOut>		getTypeTab(void)
{
  std::vector<nts::InOut>		out;

  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::POWER);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  out.push_back(nts::OUTPUT);
  out.push_back(nts::INPUT);
  return (out);
}

nts::comp4069::comp4069(const std::string& name)
  : AComponent(getTypeTab(), name)
{
  this->_gates[2] = new nts::invertGate;
  this->_gates[4] = new nts::invertGate;
  this->_gates[6] = new nts::invertGate;
  this->_gates[8] = new nts::invertGate;
  this->_gates[10] = new nts::invertGate;
  this->_gates[12] = new nts::invertGate;
}

nts::comp4069::~comp4069()
{
}

void		nts::comp4069::linkGates()
{
  for (size_t idx = 0; idx < this->_pins.size(); idx++)
    {
      if (this->_pins[idx].inOut == nts::OUTPUT)
	{
	  if (idx <= 6)
	    this->_gates[idx + 1]->editEntrie(0, this->_pins[idx - 1].state);
	  else
	    this->_gates[idx + 1]->editEntrie(0, this->_pins[idx + 1].state);
	}
    }
}

nts::Tristate	nts::comp4069::Compute(size_t pin_num_this)
{
  if (pin_num_this < 7)
    getInLinkState(pin_num_this - 1);
  else
    getInLinkState(pin_num_this + 1);
  this->linkGates();
  return (this->_gates[pin_num_this]->compute());
}
