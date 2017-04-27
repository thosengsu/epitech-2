#include <vector>
#include "nandGate.hh"
#include "IComponent.hh"

nts::nandGate::~nandGate() {
}

nts::nandGate::nandGate() : Agates()
{
  for (size_t idx = 0; idx < 2; idx++)
    this->_inState.push_back(nts::UNDEFINED);
}

nts::nandGate::nandGate(size_t nbInputs, std::vector<nts::Tristate> states)
  : Agates(nbInputs, states)
{
}

nts::Tristate		nts::nandGate::compute()
{
  if (this->getInState(0) == nts::TRUE && this->getInState(1) == nts::TRUE)
    {
      this->setOutState(nts::FALSE);
      return (nts::FALSE);
    }
  else if ((this->getInState(0) == nts::FALSE && this->getInState(1) == nts::TRUE) ||
	   (this->getInState(0) == nts::TRUE && this->getInState(1) == nts::FALSE) ||
	   (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::FALSE))
    {
      this->setOutState(nts::TRUE);
      return (nts::TRUE);
    }
  else
    {
      this->setOutState(nts::UNDEFINED);
      return (nts::UNDEFINED);
    }
  return (nts::UNDEFINED);
}
