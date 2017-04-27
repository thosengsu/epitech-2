#include <vector>
#include "Agates.hh"
#include "IComponent.hh"

nts::Agates::Agates()
{
  this->_outState = nts::UNDEFINED;
}

nts::Agates::Agates(size_t nbInputs, std::vector<nts::Tristate> stateIn)
{
  this->_outState = nts::UNDEFINED;
  for (size_t idx = 0; idx < nbInputs; idx++)
    this->_inState.push_back(stateIn[idx]);
}

nts::Agates::~Agates()
{
}

//member functions

void			nts::Agates::editEntrie(size_t numEntrie, nts::Tristate state)
{
  this->_inState[numEntrie] = state;
}

//getters

nts::Tristate		nts::Agates::getOutState() const
{
  return (this->_outState);
}

nts::Tristate		nts::Agates::getInState(int nb) const
{
  return (this->_inState[nb]);
}

size_t			nts::Agates::getNbInputs() const
{
  return (this->_inState.size());
}

std::vector<nts::Tristate>	nts::Agates::getVecInputs() const
{
  return (this->_inState);
}

//setters

void			nts::Agates::setOutState(nts::Tristate state)
{
  this->_outState = state;
}

void			nts::Agates::setNewInput(nts::Tristate state)
{
  this->_inState.push_back(state);
}
