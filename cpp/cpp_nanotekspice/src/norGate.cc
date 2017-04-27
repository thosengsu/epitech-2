#include <iostream>

#include "Agates.hh"
#include "norGate.hh"
#include "IComponent.hh"

nts::norGate::norGate() : Agates()
{
  for (size_t idx = 0; idx < 2; idx++)
    this->_inState.push_back(nts::UNDEFINED);
}

nts::norGate::norGate(size_t nbInputs, std::vector<nts::Tristate> states)
  : Agates(nbInputs, states)
{
}

nts::norGate::~norGate()
{
}

nts::Tristate		nts::norGate::compute()
{
  if (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::FALSE)
    {
      this->setOutState(nts::TRUE);
      return (nts::TRUE);
    }
  else if ((this->getInState(0) == nts::TRUE && this->getInState(1) == nts::FALSE) ||
	   (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::TRUE) ||
	   (this->getInState(0) == nts::TRUE && this->getInState(1) == nts::TRUE))
    {
      this->setOutState(nts::FALSE);
      return (nts::FALSE);
    }
  else
    {
      this->setOutState(nts::UNDEFINED);
      return (nts::UNDEFINED);
    }
  return (nts::UNDEFINED);
}

// operator

nts::norGate&		nts::norGate::operator=(const norGate& gate)
{
  this->_inState = gate.getVecInputs();
  this->_outState = gate.getOutState();
  return (*this);
}
