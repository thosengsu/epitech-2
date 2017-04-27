#include <string>
#include "enum.hh"
#include "In.hh"

static std::vector<nts::InOut>		getTypeTab(void)
{
  std::vector<nts::InOut>	out;

  out.push_back(nts::OUTPUT);
  return (out);
}

nts::In::In(std::string const& name, nts::InputType type) : AInOut(getTypeTab(), name)
{
  this->_type = type;
  if (type == nts::InputType::TRUE)
    this->_pins[0].state = nts::TRUE;
  else if (type == nts::InputType::FALSE)
    this->_pins[0].state = nts::FALSE;
}

nts::In::~In()
{
}

nts::Tristate	nts::In::Compute(__attribute__((unused))size_t pin_num_this)
{
  return (this->getState(1));
}

void		nts::In::setPin(size_t pin, nts::Tristate state)
{
  if (this->_type != nts::InputType::TRUE && this->_type != nts::InputType::FALSE)
    this->_pins[pin - 1].state = state;
}

nts::InputType	nts::In::getInType(void) const
{
  return (this->_type);
}
