#ifndef ORGATE_HH_
# define ORGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class orGate : public nts::Agates
  {
  public :
    virtual ~orGate();
    orGate(size_t nbInputs, std::vector<nts::Tristate>);
    orGate();

    virtual nts::Tristate	compute();
  };
}

#endif // ORGATE_HH_
