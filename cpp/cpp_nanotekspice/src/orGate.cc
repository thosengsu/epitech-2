#include <vector>
#include "orGate.hh"
#include "IComponent.hh"

nts::orGate::~orGate() {
}

nts::orGate::orGate(size_t nbInputs, std::vector<nts::Tristate> inStates)
  : Agates(nbInputs, inStates) {
}

nts::orGate::orGate() : Agates()
{
  for (size_t idx=0; idx < 2; idx++)
    this->_inState.push_back(nts::UNDEFINED);
}

nts::Tristate		nts::orGate::compute()
{
  if (this->getInState(0) == nts::TRUE || this->getInState(1) == nts::TRUE)
    {
      this->setOutState(nts::TRUE);
      return (nts::TRUE);
    }
  else if (this->getInState(0) == nts::FALSE || this->getInState(1) == nts::FALSE)
    {
      this->setOutState(nts::FALSE);
      return (nts::FALSE);
    }
  else
    {
      this->setOutState(nts::FALSE);
      return (nts::UNDEFINED);
    }
  return (nts::UNDEFINED);
}
