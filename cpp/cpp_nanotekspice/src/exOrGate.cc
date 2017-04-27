#include <vector>
#include "exOrGate.hh"
#include "IComponent.hh"

nts::exOrGate::~exOrGate()
{
}

nts::exOrGate::exOrGate()
{
  for (size_t idx = 0; idx < 2; idx++)
    this->_inState.push_back(nts::UNDEFINED);
}

nts::exOrGate::exOrGate(size_t nbInputs, std::vector<nts::Tristate> states)
  : Agates(nbInputs, states) {
}

nts::Tristate		nts::exOrGate::compute()
{
  if (this->getInState(0) == nts::TRUE || this->getInState(1) == nts::TRUE)
    {
      if (this->getInState(0) == nts::TRUE && this->getInState(1) == nts::TRUE)
	{
	  this->setOutState(nts::FALSE);
	  return (nts::FALSE);
	}
      else
	{
	  this->setOutState(nts::TRUE);
	  return (nts::TRUE);
	}
    }
  else if (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::FALSE)
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
