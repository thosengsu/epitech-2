#include <string>
#include "enum.hh"
#include "Out.hh"


static std::vector<nts::InOut>		getTypeTab(void)
{
  std::vector<nts::InOut>		out;

  out.push_back(nts::INPUT);
  return (out);
}

nts::Out::Out(std::string const& name) : AInOut(getTypeTab(), name)
{
}

nts::Out::~Out()
{
}

nts::Tristate	nts::Out::Compute(__attribute__((unused))size_t pin_num_this)
{
  this->setPin(1, this->getInLinkState(1));
  return (this->_pins[0].state);
}
