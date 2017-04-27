#include <vector>
#include "invertGate.hh"
#include "IComponent.hh"

nts::invertGate::~invertGate() {
}

nts::invertGate::invertGate() : Agates()
{
  this->_inState.push_back(nts::UNDEFINED);
}

nts::invertGate::invertGate(size_t nbInputs, std::vector<nts::Tristate> stateIn)
  : Agates(nbInputs, stateIn)
{
}

nts::Tristate	nts::invertGate::compute()
{
  if (this->getInState(0) == nts::TRUE)
    {
      this->setOutState(nts::FALSE);
      return (nts::FALSE);
    }
  else if (this->getInState(0) == nts::FALSE)
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

// operator

nts::invertGate&	nts::invertGate::operator=(const nts::invertGate& gate)
{
  this->_inState = gate.getVecInputs();
  this->_outState = gate.getOutState();
  return (*this);
}
