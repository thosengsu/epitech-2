#include "andGate.hh"
#include "IComponent.hh"

nts::andGate::~andGate() {
}

nts::andGate::andGate() : Agates()
{
  for (size_t idx = 0; idx < 2; idx++)
    this->_inState.push_back(nts::UNDEFINED);
}

nts::andGate::andGate(size_t nbInputs, std::vector<nts::Tristate> states)
  :Agates(nbInputs, states)
{
}

nts::Tristate		nts::andGate::compute()
{
  if (this->getInState(0) == nts::TRUE && this->getInState(1) == nts::TRUE)
    {
      this->setOutState(nts::TRUE);
      return (nts::TRUE);
    }
  else if ((this->getInState(0) == nts::TRUE && this->getInState(1) == nts::FALSE) ||
	   (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::TRUE) ||
	   (this->getInState(0) == nts::FALSE && this->getInState(1) == nts::TRUE))
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
